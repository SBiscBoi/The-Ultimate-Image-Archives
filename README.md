# The Ultimate Image Archives
This is a fan-made creation of the [Library of Babel Image Archives](https://babelia.libraryofbabel.info/),  with a much higher color scale (Full 8-bit RGB) and resolution (1920 x 1080).  The program runs on both Python and C++, with the python script handling mostly creating and displaying the image and the c++ program transforming a short input into a full-scale HD digital image.

## What is the Library of Babel Image Archives?
The original Library of Babel Image Archives (which from this point onward will be referred to as "LOBIA") was created by [Jonathan Basile](https://jonathanbasile.info/).  His goal was to build off of the story of ["The Library of Babel"](https://maskofreason.files.wordpress.com/2011/02/the-library-of-babel-by-jorge-luis-borges.pdf) by [Jorge Luis Borges](https://en.wikipedia.org/wiki/Jorge_Luis_Borges), and transform it into a visual experience beyond text.  He created an interactive slideshow containing every possible digital image that could be ever be created.  While unfathomably improbable, a passerby could see pictures of their own birth, wedding, funeral, etc. with enough luck, and a lifespan longer than the estimated lifespan of the known universe.

## Why recreate LOBIA?
There is a major drawback to Basile's implementation of LOBIA.  That drawback being that the images themselves are not the most appealing even if you were to find something other than pure noise.  The resolution of the original LOBIA is only 640x416, and the amount of possible colors is only 4096.  While the speed of generating these images is incredible, the result can be slightly underwhelming for an age where 8K monitors can be obtained by anyone with anough money saved up.

## So how does it work?
1. A variable named "input" in the main.py script takes in a string containing pure digits, character data, or both.  This is converted to a readable format and written to a file.
2. The newly created file is read by the main.cpp program and used to create the rest of the color values of the image.  These values are written to another file.
3. The most recently created file is read by the main.py script and all color values inside are used to output the final image.