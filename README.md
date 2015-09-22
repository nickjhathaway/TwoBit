# 2-bit reader

This is a (work in progress) reader implementation, based on the
specs at UCSC, http://genome.ucsc.edu/FAQ/FAQformat#format7. The
implementation is intended to be more or less thread safe; to achieve
that, each TwoBitSequence has it's own read-only file handle to the 2-bit
data.

## TODO
- probably take out buffering and rely on ifstream, see https://stackoverflow.com/questions/12757904/how-to-optimize-reading-and-writing-by-playing-with-buffer-size.  
- make TwoBitSequence in input stream? https://stackoverflow.com/questions/14086417/how-to-write-custom-input-stream-in-c

## Example use
The following converts a 2-bit file into FASTA format, on stdout.
```{C++}
TwoBit::TwoBitFile f("/home/vanderva/.ucscgenome/hg19.2bit");
std::string buffer;
for (const std::string& s : f.sequenceNames())
{
	f[s].getSequence(buffer);
	std::cout << ">" << s << std::endl;
	for (uint32_t i = 0; i < buffer.size(); i += 80)
	{
		std::cout << buffer.substr(i, 80) << '\n';
	}
	std::cout.flush();
}
```
