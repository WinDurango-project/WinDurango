"""
For use with the generate progress workflow
"""

import os
import json

def parse_exports_def(def_path):
    exports_def = set()
    with open(def_path, 'r') as def_file:
        for line in def_file:
            line = line.strip()
            if '=' in line:
                function_name = line.split('=')[0].strip()
                exports_def.add(function_name)
            elif ' ' in line:
                function_name = line.split()[0].strip()
                exports_def.add(function_name)
    return exports_def

def parse_exports_txt(txt_path):
    exports_txt = set()
    with open(txt_path, 'r') as txt_file:
        for line in txt_file:
            function_name = line.split()[0].strip()
            exports_txt.add(function_name)
    return exports_txt

def calculate_progress(def_exports, txt_exports):
    total = len(txt_exports)
    if total == 0:
        return 0
    matched = len(def_exports.intersection(txt_exports))
    progress = (matched / total) * 100
    return round(progress, 2)

def get_color_from_progress(progress):
    if progress <= 50:
        # Red to yellow (0% to 50%)
        red = 255
        green = int((progress / 50) * 255)
        blue = 0
    else:
        # Yellow to green (50% to 100%)
        red = int(255 - ((progress - 50) / 50) * 255)
        green = 255
        blue = 0
    
    return f"#{red:02x}{green:02x}{blue:02x}"

def save_progress_data(dll_name, progress):
    color = get_color_from_progress(progress)
    
    progress_data = {
        "schemaVersion": 1,
        "label": dll_name,
        "message": f"{progress}%",
        "color": color
    }
    
    output_dir = '.github/progress'
    os.makedirs(output_dir, exist_ok=True)
    output_file = os.path.join(output_dir, f'{dll_name}.json')
    
    with open(output_file, 'w') as json_file:
        json.dump(progress_data, json_file, indent=4)

def process_dll_folder(dll_folder):
    def_path = os.path.join(dll_folder, 'Exports.def')
    txt_path = os.path.join(dll_folder, 'Exports.txt')
    
    if os.path.exists(def_path) and os.path.exists(txt_path):
        dll_name = os.path.basename(dll_folder)
        def_exports = parse_exports_def(def_path)
        txt_exports = parse_exports_txt(txt_path)
        progress = calculate_progress(def_exports, txt_exports)
        save_progress_data(dll_name, progress)
        print(f"Processed {dll_name}: {progress}%")

def main():
    dlls_dir = 'dlls'
    
    if not os.path.exists(dlls_dir):
        print(f"Directory '{dlls_dir}' does not exist. Exiting!")
        return

    for root, dirs, files in os.walk(dlls_dir):
        for dir_name in dirs:
            dll_folder = os.path.join(root, dir_name)
            process_dll_folder(dll_folder)

if __name__ == '__main__':
    main()
