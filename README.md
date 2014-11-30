# 2-bit reader

This is a (work in progress) reader implementation, based on the
specs at UCSC, http://genome.ucsc.edu/FAQ/FAQformat#format7. The
implementation is intended to be more or less thread safe. each
TwoBitSequence has it's own read-only access to the 2-bit data.

## TODO
- fix extra nucleotides at byte boundaries

