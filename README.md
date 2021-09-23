# RZGT - Recursive Zip Generation Tool

RZGT is a tool made with c++ that uses 7za to create "zip bombs"

# How to use it
if you start the binary without any arg it will generate a zip with 5 layers, containing 5 files each, each "master file" (file in the root of the zip) with 1 Kb, leading to 3125 (if I didn't wrong the math) master files or 3mb of master files

if you want to customize the layer count, count of files per each, and size of master file, you need to start the RZGT with the following args:

`--lamount <number>` number of layers (ex: if I want 16 layers deep file: `--lamount 16`)<br>
`--lsize <number>` count of files for each layer (ex: if I want 6 files for each layer: `--lsize 6`)<br>
`--fsize <number>` set the size of the master file (in bytes) (ex: if I want a 1 MB master file: `--fsize  1.048.576`)<br>

# FAQ

## why "zip bombs" (with the quotation marks)
because I don't really know if this can be considered a zip bomb, I just made it based on my way of interpreting the thing

## why is the master file generation tooooooooooo slow
because it appends byte per byte in a string in a simple loop (looking for optimizations)

## is this linux compatible
maybe? i created it in windows for windows so idk if something will break on linux
