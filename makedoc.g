#
# meataxe64: meataxe64
#
# This file is a script which compiles the package manual.
#
if fail = LoadPackage("AutoDoc", "2016.02.16") then
    Error("AutoDoc version 2016.02.16 or newer is required.");
fi;

AutoDoc( rec( scaffold := true, autodoc := rec(files := ["doc/Chapters.autodoc"] )) );

QUIT_GAP();


