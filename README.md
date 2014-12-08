# 2-bit reader

This is a (work in progress) reader implementation, based on the
specs at UCSC, http://genome.ucsc.edu/FAQ/FAQformat#format7. The
implementation is intended to be more or less thread safe; to achieve
that, each TwoBitSequence has it's own read-only file handle to the 2-bit
data.

## TODO
- probably take out buffering and rely on ifstream, see https://stackoverflow.com/questions/12757904/how-to-optimize-reading-and-writing-by-playing-with-buffer-size.  
- make TwoBitSequence in input stream? https://stackoverflow.com/questions/14086417/how-to-write-custom-input-stream-in-c


