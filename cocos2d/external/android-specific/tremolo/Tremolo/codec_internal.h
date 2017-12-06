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

 function: libvorbis codec headers

 ************************************************************************/

#ifndef _V_CODECI_H_
#define _V_CODECI_H_

#define CHUNKSIZE 1024

#include "codebook.h"
#include "ivorbiscodec.h"

#define VI_TRANSFORMB 1
#define VI_WINDOWB 1
#define VI_TIMEB 1
#define VI_FLOORB 2
#define VI_RESB 3
#define VI_MAPB 1

typedef void vorbis_info_floor;

/* vorbis_dsp_state buffers the current vorbis audio
   analysis/synthesis state.  The DSP state belongs to a specific
   logical bitstream ****************************************************/
struct vorbis_dsp_state{
  vorbis_info    *vi;
  oggpack_buffer  opb;

  ogg_int32_t   **work;
  ogg_int32_t   **mdctright;
  int             out_begin;
  int             out_end;

  long lW;
  long W;

  ogg_int64_t granulepos;
  ogg_int64_t sequence;
  ogg_int64_t sample_count;

};


/* Floor backend generic *****************************************/

extern vorbis_info_floor *floor0_info_unpack(vorbis_info *,oggpack_buffer *);
extern void floor0_free_info(vorbis_info_floor *);
extern int floor0_memosize(vorbis_info_floor *);
extern ogg_int32_t *floor0_inverse1(struct vorbis_dsp_state *,
				    vorbis_info_floor *,ogg_int32_t *);
extern int floor0_inverse2 (struct vorbis_dsp_state *,vorbis_info_floor *,
			    ogg_int32_t *buffer,ogg_int32_t *);

extern vorbis_info_floor *floor1_info_unpack(vorbis_info *,oggpack_buffer *);
extern void floor1_free_info(vorbis_info_floor *);
extern int floor1_memosize(vorbis_info_floor *);
extern ogg_int32_t *floor1_inverse1(struct vorbis_dsp_state *,
				    vorbis_info_floor *,ogg_int32_t *);
extern int floor1_inverse2 (struct vorbis_dsp_state *,vorbis_info_floor *,
			    ogg_int32_t *buffer,ogg_int32_t *);

typedef struct{
  int   order;
  long  rate;
  long  barkmap;

  int   ampbits;
  int   ampdB;

  int   numbooks; /* <= 16 */
  char  books[16];

} vorbis_info_floor0;

typedef struct{
  char  class_dim;        /* 1 to 8 */
  char  class_subs;       /* 0,1,2,3 (bits: 1<<n poss) */
  unsigned char  class_book;       /* subs ^ dim entries */
  unsigned char  class_subbook[8]; /* [VIF_CLASS][subs] */
} floor1class;

typedef struct{
  floor1class  *klass;          /* [VIF_CLASS] */
  ogg_uint8_t  *partitionclass; /* [VIF_PARTS]; 0 to 15 */
  ogg_uint16_t *postlist;       /* [VIF_POSIT+2]; first two implicit */
  ogg_uint8_t  *forward_index;  /* [VIF_POSIT+2]; */
  ogg_uint8_t  *hineighbor;     /* [VIF_POSIT]; */
  ogg_uint8_t  *loneighbor;     /* [VIF_POSIT]; */

  int          partitions;    /* 0 to 31 */
  int          posts;
  int          mult;          /* 1 2 3 or 4 */

} vorbis_info_floor1;

/* Residue backend generic *****************************************/

typedef struct vorbis_info_residue{
  int type;
  unsigned char *stagemasks;
  unsigned char *stagebooks;

/* block-partitioned VQ coded straight residue */
  long begin;
  long end;

  /* first stage (lossless partitioning) */
  int           grouping;         /* group n vectors per partition */
  char          partitions;       /* possible codebooks for a partition */
  unsigned char groupbook;        /* huffbook for partitioning */
  char          stages;
} vorbis_info_residue;

extern void res_clear_info(vorbis_info_residue *info);
extern int res_unpack(vorbis_info_residue *info,
		      vorbis_info *vi,oggpack_buffer *opb);
extern int res_inverse(vorbis_dsp_state *,vorbis_info_residue *info,
		       ogg_int32_t **in,int *nonzero,int ch);

/* mode ************************************************************/
typedef struct {
  unsigned char blockflag;
  unsigned char mapping;
} vorbis_info_mode;

/* Mapping backend generic *****************************************/
typedef struct coupling_step{
  unsigned char mag;
  unsigned char ang;
} coupling_step;

typedef struct submap{
  char floor;
  char residue;
} submap;

typedef struct vorbis_info_mapping{
  int            submaps;

  unsigned char *chmuxlist;
  submap        *submaplist;

  int            coupling_steps;
  coupling_step *coupling;
} vorbis_info_mapping;

extern int mapping_info_unpack(vorbis_info_mapping *,vorbis_info *,
			       oggpack_buffer *);
extern void mapping_clear_info(vorbis_info_mapping *);
extern int mapping_inverse(struct vorbis_dsp_state *,vorbis_info_mapping *);

/* codec_setup_info contains all the setup information specific to the
   specific compression/decompression mode in progress (eg,
   psychoacoustic settings, channel setup, options, codebook
   etc).
*********************************************************************/

typedef struct codec_setup_info {

  /* Vorbis supports only short and long blocks, but allows the
     encoder to choose the sizes */

  long blocksizes[2];

  /* modes are the primary means of supporting on-the-fly different
     blocksizes, different channel mappings (LR or M/A),
     different residue backends, etc.  Each mode consists of a
     blocksize flag and a mapping (along with the mapping setup */

  int        modes;
  int        maps;
  int        floors;
  int        residues;
  int        books;

  vorbis_info_mode       *mode_param;
  vorbis_info_mapping    *map_param;
  char                   *floor_type;
  vorbis_info_floor     **floor_param;
  vorbis_info_residue    *residue_param;
  codebook               *book_param;

} codec_setup_info;

extern int      vorbis_dsp_init(vorbis_dsp_state *v, vorbis_info *vi);
extern void     vorbis_dsp_clear(vorbis_dsp_state *v);
extern vorbis_dsp_state *vorbis_dsp_create(vorbis_info *vi);
extern void     vorbis_dsp_destroy(vorbis_dsp_state *v);
extern int      vorbis_dsp_headerin(vorbis_info *vi,vorbis_comment *vc,
				    ogg_packet *op);

extern int      vorbis_dsp_restart(vorbis_dsp_state *v);
extern int      vorbis_dsp_synthesis(vorbis_dsp_state *vd,
				     ogg_packet *op,int decodep);
extern int      vorbis_dsp_pcmout(vorbis_dsp_state *v,
				  ogg_int16_t *pcm,int samples);
extern int      vorbis_dsp_read(vorbis_dsp_state *v,int samples);
extern long     vorbis_packet_blocksize(vorbis_info *vi,ogg_packet *op);



#endif
