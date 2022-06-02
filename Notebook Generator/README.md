# notebook-generator

    Usage: ./bin/notebook <source_dir> [options]

    Auto generate notebooks from your source code

    Options:
        -V, --version             output the version number
        -a --author <name>        author's name to be added in the notebook
        -i --initials <initials>  initials of the author to be placed in the upper-right corner of all pages
        -o --output <filename>    output file for the notebook. (default: "./notebook.pdf")
        -s --size <size>          font size is allowed 8, 9, 10, 11, 12, 14, 17, 20 pt (default: "10")
        -c --columns <amount>     number of columns is allowed 2, 3. (default: "2")
        -p --paper <size>         paper size is allowed letterpaper, a4paper, a5paper. (default: "letterpaper")
        -h, --help                output usage information
        -I --image <source>       cover image to be added in the notebook.



example:
    ./bin/notebookgen -s 11 -c 3 -p a4paper -a "BUET Radiant" ./Compressed/
    ./bin/notebookgen -s 10 -c 3 -p a4paper -a "BUET Beggar Bros - Bangladesh University of Engineering and Technology" ./../src/

For more details and source project see: https://github.com/pin3da/notebook-generator
