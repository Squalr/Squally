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
        
        if image_format != 'tiff':
            return

        # Open the TIFF image
        tiff_img = Image.open(BytesIO(image_data))

        # Convert to PNG and save to a BytesIO object
        png_bytes = BytesIO()
        tiff_img.save(png_bytes, format='PNG')

        # Encode PNG image to base64
        png_base64 = base64.b64encode(png_bytes.getvalue()).decode('utf-8')

        # Update plist with new PNG base64 string and save it
        plist_data["textureImageData"] = png_base64
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
