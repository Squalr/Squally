import os
import base64
import plistlib
import imghdr
from PIL import Image
from io import BytesIO

def process_plist(file_path):
    # Load plist file
    with open(file_path, 'rb') as plist_file:
        plist_data = plistlib.load(plist_file)

    # If the textureImageData key exists in the plist
    if "textureImageData" in plist_data:
        image_base64 = plist_data["textureImageData"]

        # Decode base64
        image_data = base64.b64decode(image_base64)

        # Determine the image format
        image_format = imghdr.what(None, image_data)
        
        if image_format != 'png':
            return

        # Open the PNG image
        png_img = Image.open(BytesIO(image_data))

        # Convert to TIFF and save to a BytesIO object
        tiff_bytes = BytesIO()
        png_img.save(tiff_bytes, format='TIFF')

        # Encode TIFF image to base64
        tiff_base64 = base64.b64encode(tiff_bytes.getvalue()).decode('utf-8')

        # Update plist with new TIFF base64 string and save it
        plist_data["textureImageData"] = tiff_base64
        with open(file_path, 'wb') as plist_file:
            print(file_path)
            plistlib.dump(plist_data, plist_file)

def process_directory(directory):
    for root, dirs, files in os.walk(directory):
        for file in files:
            if file.endswith('.plist'):
                process_plist(os.path.join(root, file))

# Start the processing from the current directory
process_directory(os.getcwd())
