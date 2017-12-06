/************************************************************************
 * Copyright (C) 2002-2009, Xiph.org Foundation
 * Copyright (C) 2010, Robin Watts for Pinknoise Productions Ltd
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the names of the Xiph.org Foundation nor Pinknoise
 * Productions Ltd nor the names of its contributors may be used to
 * endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ************************************************************************

 function: basic codebook pack/unpack/code/decode operations

 ************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
// #include <log/log.h>
#include "ogg.h"
#include "ivorbiscodec.h"
#include "codebook.h"
#include "misc.h"
#include "os.h"

#define MARKER_SIZE 33

/**** pack/unpack helpers ******************************************/
int _ilog(unsigned int v){
  int ret=0;
  while(v){
    ret++;
    v>>=1;
  }
  return(ret);
}

static ogg_uint32_t decpack(long entry,long used_entry,long quantvals,
			    codebook *b,oggpack_buffer *opb,int maptype){
  ogg_uint32_t ret=0;
  int j;

  switch(b->dec_type){

  case 0:
    return (ogg_uint32_t)entry;

  case 1:
    if(maptype==1){
      /* vals are already read into temporary column vector here */
      for(j=0;j<b->dim;j++){
	ogg_uint32_t off=entry%quantvals;
	entry/=quantvals;
	ret|=((ogg_uint16_t *)(b->q_val))[off]<<(b->q_bits*j);
      }
    }else{
      for(j=0;j<b->dim;j++)
	ret|=oggpack_read(opb,b->q_bits)<<(b->q_bits*j);
    }
    return ret;

  case 2:
    for(j=0;j<b->dim;j++){
      ogg_uint32_t off=entry%quantvals;
      entry/=quantvals;
      ret|=off<<(b->q_pack*j);
    }
    return ret;

  case 3:
    return (ogg_uint32_t)used_entry;

  }
  return 0; /* silence compiler */
}

/* 32 bit float (not IEEE; nonnormalized mantissa +
   biased exponent) : neeeeeee eeemmmmm mmmmmmmm mmmmmmmm
   Why not IEEE?  It's just not that important here. */

static ogg_int32_t _float32_unpack(long val,int *point){
  long   mant=val&0x1fffff;
  int    sign=val&0x80000000;

  *point=((val&0x7fe00000L)>>21)-788;

  if(mant){
    while(!(mant&0x40000000)){
      mant<<=1;
      *point-=1;
    }
    if(sign)mant= -mant;
  }else{
    *point=-9999;
  }
  return mant;
}

/* choose the smallest supported node size that fits our decode table.
   Legal bytewidths are 1/1 1/2 2/2 2/4 4/4 */
static int _determine_node_bytes(long used, int leafwidth){

  /* special case small books to size 4 to avoid multiple special
     cases in repack */
  if(used<2)
    return 4;

  if(leafwidth==3)leafwidth=4;
  if(_ilog(3*used-6)+1 <= leafwidth*4)
    return leafwidth/2?leafwidth/2:1;
  return leafwidth;
}

/* convenience/clarity; leaves are specified as multiple of node word
   size (1 or 2) */
static int _determine_leaf_words(int nodeb, int leafwidth){
  if(leafwidth>nodeb)return 2;
  return 1;
}

/* given a list of word lengths, number of used entries, and byte
   width of a leaf, generate the decode table */
static int _make_words(char *l,long n,ogg_uint32_t *r,long quantvals,
		       codebook *b, oggpack_buffer *opb,int maptype){
  long i,j,count=0;
  long top=0;
  ogg_uint32_t marker[MARKER_SIZE];

  if (n<1)
    return 1;

  if(n<2){
    r[0]=0x80000000;
  }else{
    memset(marker,0,sizeof(marker));

    for(i=0;i<n;i++){
      long length=l[i];
      if(length){
        if (length < 0 || length >= MARKER_SIZE) {
          //cjh ALOGE("b/23881715");
          return 1;
        }
	ogg_uint32_t entry=marker[length];
	long chase=0;
	if(count && !entry)return -1; /* overpopulated tree! */

	/* chase the tree as far as it's already populated, fill in past */
	for(j=0;j<length-1;j++){
	  int bit=(entry>>(length-j-1))&1;
	  if(chase>=top){
	    if (chase < 0 || chase >= n) return 1;
	    top++;
	    r[chase*2]=top;
	    r[chase*2+1]=0;
	  }else
	    if (chase < 0 || chase >= n || chase*2+bit > n*2+1) return 1;
	    if(!r[chase*2+bit])
	      r[chase*2+bit]=top;
	  chase=r[chase*2+bit];
	  if (chase < 0 || chase >= n) return 1;
	}
	{
	  int bit=(entry>>(length-j-1))&1;
	  if(chase>=top){
	    top++;
	    r[chase*2+1]=0;
	  }
	  r[chase*2+bit]= decpack(i,count++,quantvals,b,opb,maptype) |
	    0x80000000;
	}

	/* Look to see if the next shorter marker points to the node
	   above. if so, update it and repeat.  */
	for(j=length;j>0;j--){
	  if(marker[j]&1){
	    marker[j]=marker[j-1]<<1;
	    break;
	  }
	  marker[j]++;
	}

	/* prune the tree; the implicit invariant says all the longer
	   markers were dangling from our just-taken node.  Dangle them
	   from our *new* node. */
	for(j=length+1;j<MARKER_SIZE;j++)
	  if((marker[j]>>1) == entry){
	    entry=marker[j];
	    marker[j]=marker[j-1]<<1;
	  }else
	    break;
      }
    }
  }

  // following sanity check copied from libvorbis
  /* sanity check the huffman tree; an underpopulated tree must be
     rejected. The only exception is the one-node pseudo-nil tree,
     which appears to be underpopulated because the tree doesn't
     really exist; there's only one possible 'codeword' or zero bits,
     but the above tree-gen code doesn't mark that. */
  if(b->used_entries != 1){
    for(i=1;i<MARKER_SIZE;i++)
      if(marker[i] & (0xffffffffUL>>(32-i))){
          return 1;
      }
  }


  return 0;
}

static int _make_decode_table(codebook *s,char *lengthlist,long quantvals,
			      oggpack_buffer *opb,int maptype){
  int i;
  ogg_uint32_t *work;

  if (!lengthlist) return 1;
  if(s->dec_nodeb==4){
    /* Over-allocate by using s->entries instead of used_entries.
     * This means that we can use s->entries to enforce size in
     * _make_words without messing up length list looping.
     * This probably wastes a bit of space, but it shouldn't
     * impact behavior or size too much.
     */
    s->dec_table=_ogg_malloc((s->entries*2+1)*sizeof(*work));
    if (!s->dec_table) return 1;
    /* +1 (rather than -2) is to accommodate 0 and 1 sized books,
       which are specialcased to nodeb==4 */
    if(_make_words(lengthlist,s->entries,
		   s->dec_table,quantvals,s,opb,maptype))return 1;

    return 0;
  }

  if (s->used_entries > INT_MAX/2 ||
      s->used_entries*2 > INT_MAX/((long) sizeof(*work)) - 1) return 1;
  /* Overallocate as above */
  work=calloc((s->entries*2+1),sizeof(*work));
  if (!work) return 1;
  if(_make_words(lengthlist,s->entries,work,quantvals,s,opb,maptype)) goto error_out;
  if (s->used_entries > INT_MAX/(s->dec_leafw+1)) goto error_out;
  if (s->dec_nodeb && s->used_entries * (s->dec_leafw+1) > INT_MAX/s->dec_nodeb) goto error_out;
  s->dec_table=_ogg_malloc((s->used_entries*(s->dec_leafw+1)-2)*
			   s->dec_nodeb);
  if (!s->dec_table) goto error_out;

  if(s->dec_leafw==1){
    switch(s->dec_nodeb){
    case 1:
      for(i=0;i<s->used_entries*2-2;i++)
	  ((unsigned char *)s->dec_table)[i]=(unsigned char)
	    (((work[i] & 0x80000000UL) >> 24) | work[i]);
      break;
    case 2:
      for(i=0;i<s->used_entries*2-2;i++)
	  ((ogg_uint16_t *)s->dec_table)[i]=(ogg_uint16_t)
	    (((work[i] & 0x80000000UL) >> 16) | work[i]);
      break;
    }

  }else{
    /* more complex; we have to do a two-pass repack that updates the
       node indexing. */
    long top=s->used_entries*3-2;
    if(s->dec_nodeb==1){
      unsigned char *out=(unsigned char *)s->dec_table;

      for(i=s->used_entries*2-4;i>=0;i-=2){
	if(work[i]&0x80000000UL){
	  if(work[i+1]&0x80000000UL){
	    top-=4;
	    out[top]=(work[i]>>8 & 0x7f)|0x80;
	    out[top+1]=(work[i+1]>>8 & 0x7f)|0x80;
	    out[top+2]=work[i] & 0xff;
	    out[top+3]=work[i+1] & 0xff;
	  }else{
	    top-=3;
	    out[top]=(work[i]>>8 & 0x7f)|0x80;
	    out[top+1]=work[work[i+1]*2];
	    out[top+2]=work[i] & 0xff;
	  }
	}else{
	  if(work[i+1]&0x80000000UL){
	    top-=3;
	    out[top]=work[work[i]*2];
	    out[top+1]=(work[i+1]>>8 & 0x7f)|0x80;
	    out[top+2]=work[i+1] & 0xff;
	  }else{
	    top-=2;
	    out[top]=work[work[i]*2];
	    out[top+1]=work[work[i+1]*2];
	  }
	}
	work[i]=top;
      }
    }else{
      ogg_uint16_t *out=(ogg_uint16_t *)s->dec_table;
      for(i=s->used_entries*2-4;i>=0;i-=2){
	if(work[i]&0x80000000UL){
	  if(work[i+1]&0x80000000UL){
	    top-=4;
	    out[top]=(work[i]>>16 & 0x7fff)|0x8000;
	    out[top+1]=(work[i+1]>>16 & 0x7fff)|0x8000;
	    out[top+2]=work[i] & 0xffff;
	    out[top+3]=work[i+1] & 0xffff;
	  }else{
	    top-=3;
	    out[top]=(work[i]>>16 & 0x7fff)|0x8000;
	    out[top+1]=work[work[i+1]*2];
	    out[top+2]=work[i] & 0xffff;
	  }
	}else{
	  if(work[i+1]&0x80000000UL){
	    top-=3;
	    out[top]=work[work[i]*2];
	    out[top+1]=(work[i+1]>>16 & 0x7fff)|0x8000;
	    out[top+2]=work[i+1] & 0xffff;
	  }else{
	    top-=2;
	    out[top]=work[work[i]*2];
	    out[top+1]=work[work[i+1]*2];
	  }
	}
	work[i]=top;
      }
    }
  }

  free(work);
  return 0;
error_out:
  free(work);
  return 1;
}

/* most of the time, entries%dimensions == 0, but we need to be
   well defined.  We define that the possible vales at each
   scalar is values == entries/dim.  If entries%dim != 0, we'll
   have 'too few' values (values*dim<entries), which means that
   we'll have 'left over' entries; left over entries use zeroed
   values (and are wasted).  So don't generate codebooks like
   that */
/* there might be a straightforward one-line way to do the below
   that's portable and totally safe against roundoff, but I haven't
   thought of it.  Therefore, we opt on the side of caution */
long _book_maptype1_quantvals(codebook *b){
  /* get us a starting hint, we'll polish it below */
  int bits=_ilog(b->entries);
  int vals=b->entries>>((bits-1)*(b->dim-1)/b->dim);

  while(1){
    long acc=1;
    long acc1=1;
    int i;
    for(i=0;i<b->dim;i++){
      acc*=vals;
      acc1*=vals+1;
    }
    if(acc<=b->entries && acc1>b->entries){
      return(vals);
    }else{
      if(acc>b->entries){
        vals--;
      }else{
        vals++;
      }
    }
  }
}

void vorbis_book_clear(codebook *b){
  /* static book is not cleared; we're likely called on the lookup and
     the static codebook belongs to the info struct */
  if(b->q_val)_ogg_free(b->q_val);
  if(b->dec_table)_ogg_free(b->dec_table);
  if(b->dec_buf)_ogg_free(b->dec_buf);

  memset(b,0,sizeof(*b));
}

int vorbis_book_unpack(oggpack_buffer *opb,codebook *s){
  char         *lengthlist=NULL;
  int           quantvals=0;
  long          i,j;
  int           maptype;

  memset(s,0,sizeof(*s));

  /* make sure alignment is correct */
  if(oggpack_read(opb,24)!=0x564342)goto _eofout;

  /* first the basic parameters */
  s->dim=oggpack_read(opb,16);
  s->dec_buf=_ogg_malloc(sizeof(ogg_int32_t)*s->dim);
  if (s->dec_buf == NULL)
      goto _errout;
  s->entries=oggpack_read(opb,24);
  if(s->entries<=0)goto _eofout;
  if(s->dim<=0)goto _eofout;
  if(_ilog(s->dim)+_ilog(s->entries)>24)goto _eofout; 
  if (s->dim > INT_MAX/s->entries) goto _eofout;

  /* codeword ordering.... length ordered or unordered? */
  switch((int)oggpack_read(opb,1)){
  case 0:
    /* unordered */
    lengthlist=(char *)calloc(s->entries, sizeof(*lengthlist));
    if(!lengthlist) goto _eofout;

    /* allocated but unused entries? */
    if(oggpack_read(opb,1)){
      /* yes, unused entries */

      for(i=0;i<s->entries;i++){
	if(oggpack_read(opb,1)){
	  long num=oggpack_read(opb,5);
	  if(num==-1)goto _eofout;
	  lengthlist[i]=(char)(num+1);
	  s->used_entries++;
	  if(num+1>s->dec_maxlength)s->dec_maxlength=num+1;
	}else
	  lengthlist[i]=0;
      }
    }else{
      /* all entries used; no tagging */
      s->used_entries=s->entries;
      for(i=0;i<s->entries;i++){
	long num=oggpack_read(opb,5);
	if(num==-1)goto _eofout;
	lengthlist[i]=(char)(num+1);
	if(num+1>s->dec_maxlength)s->dec_maxlength=num+1;
      }
    }

    break;
  case 1:
    /* ordered */
    {
      long length=oggpack_read(opb,5)+1;

      s->used_entries=s->entries;
      lengthlist=(char *)calloc(s->entries, sizeof(*lengthlist));
      if (!lengthlist) goto _eofout;

      for(i=0;i<s->entries;){
	long num=oggpack_read(opb,_ilog(s->entries-i));
	if(num<0)goto _eofout;
	for(j=0;j<num && i<s->entries;j++,i++)
	  lengthlist[i]=(char)length;
	s->dec_maxlength=length;
	length++;
      }
    }
    break;
  default:
    /* EOF */
    goto _eofout;
  }


  /* Do we have a mapping to unpack? */

  if((maptype=oggpack_read(opb,4))>0){
    s->q_min=_float32_unpack(oggpack_read(opb,32),&s->q_minp);
    s->q_del=_float32_unpack(oggpack_read(opb,32),&s->q_delp);
    s->q_bits=oggpack_read(opb,4)+1;
    s->q_seq=oggpack_read(opb,1);

    s->q_del>>=s->q_bits;
    s->q_delp+=s->q_bits;
  }

  switch(maptype){
  case 0:

    /* no mapping; decode type 0 */

    /* how many bytes for the indexing? */
    /* this is the correct boundary here; we lose one bit to
       node/leaf mark */
    s->dec_nodeb=_determine_node_bytes(s->used_entries,_ilog(s->entries)/8+1);
    s->dec_leafw=_determine_leaf_words(s->dec_nodeb,_ilog(s->entries)/8+1);
    s->dec_type=0;

    if(_make_decode_table(s,lengthlist,quantvals,opb,maptype)) goto _errout;
    break;

  case 1:

    /* mapping type 1; implicit values by lattice  position */
    quantvals=_book_maptype1_quantvals(s);

    /* dec_type choices here are 1,2; 3 doesn't make sense */
    {
      /* packed values */
      long total1=(s->q_bits*s->dim+8)/8; /* remember flag bit */
      if (s->dim > (INT_MAX-8)/s->q_bits) goto _eofout;
      /* vector of column offsets; remember flag bit */
      long total2=(_ilog(quantvals-1)*s->dim+8)/8+(s->q_bits+7)/8;


      if(total1<=4 && total1<=total2){
	/* use dec_type 1: vector of packed values */

	/* need quantized values before  */
	s->q_val=calloc(sizeof(ogg_uint16_t), quantvals);
	if (!s->q_val) goto _eofout;
	for(i=0;i<quantvals;i++)
	  ((ogg_uint16_t *)s->q_val)[i]=(ogg_uint16_t)oggpack_read(opb,s->q_bits);

	if(oggpack_eop(opb)){
	  goto _eofout;
	}

	s->dec_type=1;
	s->dec_nodeb=_determine_node_bytes(s->used_entries,
					   (s->q_bits*s->dim+8)/8);
	s->dec_leafw=_determine_leaf_words(s->dec_nodeb,
					   (s->q_bits*s->dim+8)/8);
	if(_make_decode_table(s,lengthlist,quantvals,opb,maptype)){
	  goto _errout;
	}

	free(s->q_val);
	s->q_val=0;

      }else{
	/* use dec_type 2: packed vector of column offsets */

	/* need quantized values before */
	if(s->q_bits<=8){
	  s->q_val=_ogg_malloc(quantvals);
	  if (!s->q_val) goto _eofout;
	  for(i=0;i<quantvals;i++)
	    ((unsigned char *)s->q_val)[i]=(unsigned char)oggpack_read(opb,s->q_bits);
	}else{
	  s->q_val=_ogg_malloc(quantvals*2);
	  if (!s->q_val) goto _eofout;
	  for(i=0;i<quantvals;i++)
	    ((ogg_uint16_t *)s->q_val)[i]=(ogg_uint16_t)oggpack_read(opb,s->q_bits);
	}

	if(oggpack_eop(opb))goto _eofout;

	s->q_pack=_ilog(quantvals-1);
	s->dec_type=2;
	s->dec_nodeb=_determine_node_bytes(s->used_entries,
					   (_ilog(quantvals-1)*s->dim+8)/8);
	s->dec_leafw=_determine_leaf_words(s->dec_nodeb,
					   (_ilog(quantvals-1)*s->dim+8)/8);
	if(_make_decode_table(s,lengthlist,quantvals,opb,maptype))goto _errout;

      }
    }
    break;
  case 2:

    /* mapping type 2; explicit array of values */
    quantvals=s->entries*s->dim;
    /* dec_type choices here are 1,3; 2 is not possible */

    if( (s->q_bits*s->dim+8)/8 <=4){ /* remember flag bit */
      /* use dec_type 1: vector of packed values */

      s->dec_type=1;
      s->dec_nodeb=_determine_node_bytes(s->used_entries,(s->q_bits*s->dim+8)/8);
      s->dec_leafw=_determine_leaf_words(s->dec_nodeb,(s->q_bits*s->dim+8)/8);
      if(_make_decode_table(s,lengthlist,quantvals,opb,maptype))goto _errout;

    }else{
      /* use dec_type 3: scalar offset into packed value array */

      s->dec_type=3;
      s->dec_nodeb=_determine_node_bytes(s->used_entries,_ilog(s->used_entries-1)/8+1);
      s->dec_leafw=_determine_leaf_words(s->dec_nodeb,_ilog(s->used_entries-1)/8+1);
      if(_make_decode_table(s,lengthlist,quantvals,opb,maptype))goto _errout;

      /* get the vals & pack them */
      s->q_pack=(s->q_bits+7)/8*s->dim;
      s->q_val=_ogg_malloc(s->q_pack*s->used_entries);

      if(s->q_bits<=8){
	for(i=0;i<s->used_entries*s->dim;i++)
	  ((unsigned char *)(s->q_val))[i]=(unsigned char)oggpack_read(opb,s->q_bits);
      }else{
	for(i=0;i<s->used_entries*s->dim;i++)
	  ((ogg_uint16_t *)(s->q_val))[i]=(ogg_uint16_t)oggpack_read(opb,s->q_bits);
      }
    }
    break;
  default:
    goto _errout;
  }

  if (s->dec_nodeb==1)
    if (s->dec_leafw == 1)
      s->dec_method = 0;
    else
      s->dec_method = 1;
  else if (s->dec_nodeb==2)
    if (s->dec_leafw == 1)
      s->dec_method = 2;
    else
      s->dec_method = 3;
  else
    s->dec_method = 4;

  if(oggpack_eop(opb))goto _eofout;

  free(lengthlist);
  return 0;
 _errout:
 _eofout:
  vorbis_book_clear(s);
  free(lengthlist);
  free(s->q_val);
  return -1;
}

#ifndef ONLY_C
ogg_uint32_t decode_packed_entry_number(codebook *book,
                                        oggpack_buffer *b);
#else
static inline ogg_uint32_t decode_packed_entry_number(codebook *book,
						      oggpack_buffer *b){
  ogg_uint32_t chase=0;
  int  read=book->dec_maxlength;
  long lok = oggpack_look(b,read),i;

  while(lok<0 && read>1)
    lok = oggpack_look(b, --read);

  if(lok<0){
    oggpack_adv(b,1); /* force eop */
    return -1;
  }

  /* chase the tree with the bits we got */
  switch (book->dec_method)
  {
    case 0:
    {
      /* book->dec_nodeb==1, book->dec_leafw==1 */
      /* 8/8 - Used */
      unsigned char *t=(unsigned char *)book->dec_table;

      for(i=0;i<read;i++){
	chase=t[chase*2+((lok>>i)&1)];
	if(chase&0x80UL)break;
      }
      chase&=0x7fUL;
      break;
    }
    case 1:
    {
      /* book->dec_nodeb==1, book->dec_leafw!=1 */
      /* 8/16 - Used by infile2 */
      unsigned char *t=(unsigned char *)book->dec_table;
      for(i=0;i<read;i++){
	int bit=(lok>>i)&1;
	int next=t[chase+bit];
	if(next&0x80){
	  chase= (next<<8) | t[chase+bit+1+(!bit || t[chase]&0x80)];
	  break;
	}
	chase=next;
      }
      //chase&=0x7fffUL;
      chase&=~0x8000UL;
      break;
    }
    case 2:
    {
      /* book->dec_nodeb==2, book->dec_leafw==1 */
      /* 16/16 - Used */
      for(i=0;i<read;i++){
	chase=((ogg_uint16_t *)(book->dec_table))[chase*2+((lok>>i)&1)];
	if(chase&0x8000UL)break;
      }
      //chase&=0x7fffUL;
      chase&=~0x8000UL;
      break;
    }
    case 3:
    {
      /* book->dec_nodeb==2, book->dec_leafw!=1 */
      /* 16/32 - Used by infile2 */
      ogg_uint16_t *t=(ogg_uint16_t *)book->dec_table;
      for(i=0;i<read;i++){
	int bit=(lok>>i)&1;
	int next=t[chase+bit];
	if(next&0x8000){
	  chase= (next<<16) | t[chase+bit+1+(!bit || t[chase]&0x8000)];
	  break;
	}
	chase=next;
      }
      //chase&=0x7fffffffUL;
      chase&=~0x80000000UL;
      break;
    }
    case 4:
    {
      //Output("32/32");
      for(i=0;i<read;i++){
	chase=((ogg_uint32_t *)(book->dec_table))[chase*2+((lok>>i)&1)];
	if(chase&0x80000000UL)break;
      }
      //chase&=0x7fffffffUL;
      chase&=~0x80000000UL;
      break;
    }
  }

  if(i<read){
    oggpack_adv(b,i+1);
    return chase;
  }
  oggpack_adv(b,read+1);
  return(-1);
}
#endif

/* returns the [original, not compacted] entry number or -1 on eof *********/
long vorbis_book_decode(codebook *book, oggpack_buffer *b){
  if(book->dec_type)return -1;
 return decode_packed_entry_number(book,b);
}

#ifndef ONLY_C
int decode_map(codebook *s, oggpack_buffer *b, ogg_int32_t *v, int point);
#else
static int decode_map(codebook *s, oggpack_buffer *b, ogg_int32_t *v, int point){
  ogg_uint32_t entry = decode_packed_entry_number(s,b);
  int i;
  if(oggpack_eop(b))return(-1);

  /* 1 used by test file 0 */

  /* according to decode type */
  switch(s->dec_type){
  case 1:{
    /* packed vector of values */
    int mask=(1<<s->q_bits)-1;
    for(i=0;i<s->dim;i++){
      v[i]=entry&mask;
      entry>>=s->q_bits;
    }
    break;
  }
  case 2:{
    /* packed vector of column offsets */
    int mask=(1<<s->q_pack)-1;
    for(i=0;i<s->dim;i++){
      if(s->q_bits<=8)
	v[i]=((unsigned char *)(s->q_val))[entry&mask];
      else
	v[i]=((ogg_uint16_t *)(s->q_val))[entry&mask];
      entry>>=s->q_pack;
    }
    break;
  }
  case 3:{
    /* offset into array */
    void *ptr=((char *)s->q_val)+entry*s->q_pack;

    if(s->q_bits<=8){
      for(i=0;i<s->dim;i++)
	v[i]=((unsigned char *)ptr)[i];
    }else{
      for(i=0;i<s->dim;i++)
	v[i]=((ogg_uint16_t *)ptr)[i];
    }
    break;
  }
  default:
    return -1;
  }

  /* we have the unpacked multiplicands; compute final vals */
  {
    int         shiftM = point-s->q_delp;
    ogg_int32_t add    = point-s->q_minp;
    int         mul    = s->q_del;

    if(add>0)
      add= s->q_min >> add;
    else
      add= s->q_min << -add;
    if (shiftM<0)
    {
      mul <<= -shiftM;
      shiftM = 0;
    }
    add <<= shiftM;

    for(i=0;i<s->dim;i++)
      v[i]= ((add + v[i] * mul) >> shiftM);

    if(s->q_seq)
      for(i=1;i<s->dim;i++)
	v[i]+=v[i-1];
  }

  return 0;
}
#endif

/* returns 0 on OK or -1 on eof *************************************/
long vorbis_book_decodevs_add(codebook *book,ogg_int32_t *a,
			      oggpack_buffer *b,int n,int point){
  if(book->used_entries>0){
    int step=n/book->dim;
    ogg_int32_t *v = book->dec_buf;//(ogg_int32_t *)alloca(sizeof(*v)*book->dim);
    int i,j,o;
    if (!v) return -1;

    for (j=0;j<step;j++){
      if(decode_map(book,b,v,point))return -1;
      for(i=0,o=j;i<book->dim;i++,o+=step)
	a[o]+=v[i];
    }
  }
  return 0;
}

long vorbis_book_decodev_add(codebook *book,ogg_int32_t *a,
			     oggpack_buffer *b,int n,int point){
  if(book->used_entries>0){
    ogg_int32_t *v = book->dec_buf;//(ogg_int32_t *)alloca(sizeof(*v)*book->dim);
    int i,j;

    if (!v) return -1;
    for(i=0;i<n;){
      if(decode_map(book,b,v,point))return -1;
      for (j=0;j<book->dim;j++)
	a[i++]+=v[j];
    }
  }
  return 0;
}

long vorbis_book_decodev_set(codebook *book,ogg_int32_t *a,
			     oggpack_buffer *b,int n,int point){
  if(book->used_entries>0){
    ogg_int32_t *v = book->dec_buf;//(ogg_int32_t *)alloca(sizeof(*v)*book->dim);
    int i,j;

    if (!v) return -1;
    for(i=0;i<n;){
      if(decode_map(book,b,v,point))return -1;
      for (j=0;j<book->dim;j++)
	a[i++]=v[j];
    }
  }else{
    int i,j;

    for(i=0;i<n;){
      for (j=0;j<book->dim;j++)
	a[i++]=0;
    }
  }

  return 0;
}

#ifndef ONLY_C
long vorbis_book_decodevv_add(codebook *book,ogg_int32_t **a,
			      long offset,int ch,
			      oggpack_buffer *b,int n,int point);
#else
long vorbis_book_decodevv_add(codebook *book,ogg_int32_t **a,
			      long offset,int ch,
			      oggpack_buffer *b,int n,int point){
  if(book->used_entries>0){

    ogg_int32_t *v = book->dec_buf;//(ogg_int32_t *)alloca(sizeof(*v)*book->dim);
    long i,j;
    int chptr=0;

    if (!v) return -1;
    for(i=offset;i<offset+n;){
      if(decode_map(book,b,v,point))return -1;
      for (j=0;j<book->dim;j++){
	a[chptr++][i]+=v[j];
	if(chptr==ch){
	  chptr=0;
	  i++;
	}
      }
    }
  }

  return 0;
}
#endif
