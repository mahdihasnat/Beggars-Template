#!/bin/python

import os
import sys
import pathlib

def ChangeName(d):
    return d[0].upper() + d[1:]

def remove_extension(path):
    return os.path.splitext(path)[0]

def get_extension(path):
    ext = os.path.splitext(path)[1][1:]
    if ext == "py":
        return "python"
    elif ext == None:
        return "cpp"
    else:
        return ext
    

def read_file(path):
    with open(path) as f:
        return f.read()

def walk(root,level,out_file=sys.stdout):
    sections = ["section", "subsection", "subsubsection", "paragraph", "subparagraph"]
    lst = []
    for path in root.iterdir():
        lst.append(path)
    lst = sorted(lst)
    for path in lst:
        if path.is_dir():
            print("\\" + sections[level] + "{" + ChangeName(path.name) + "}",end="\n\n",file=out_file)
            walk(path, level+1, out_file=out_file)
        else:
            print("\\" + sections[level] + "{" + ChangeName(remove_extension(path.name)) + "}",file=out_file)
            # print("\\inputminted{{{}}}{{\"{}\"}}".format(get_extension(path),path),  end="\n\n",file=out_file)
            print("""
\\begin{{minted}}{{{lang}}}
{code}
\\end{{minted}}
""".format( lang = get_extension(path), code=read_file(path)), end="\n\n",file=out_file)

TEAM_NAME = "BUET XYZ"

path =  pathlib.Path(__file__).parent.absolute()
path_src = path.joinpath("src")

with open("texcode.tex", "w") as out:
    # copy header.tex to texcode.tex
    with open("out/header.tex", "r") as header:
        out.write(header.read().replace("$TEAM_NAME$",TEAM_NAME))
    # write section and to texcode.tex
    walk(path_src,0,out_file=out)

    # copy footer.tex to texcode.tex
    with open("out/footer.tex", "r") as footer:
        out.write(footer.read())

# run command to install texlive
# os.system("sudo apt-get install texlive")
# os.system("sudo apt-get install texlive-latex-extra")
# os.system("sudo apt-get install python-pygments")

# run command to compile texcode.tex
# os.system("pdflatex -interaction=nonstopmode  -shell-escape texcode.tex")
os.system("pdflatex -shell-escape texcode.tex")
# os.system("pdflatex texcode.tex")

exit()