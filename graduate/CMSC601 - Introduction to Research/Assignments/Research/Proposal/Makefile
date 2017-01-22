
PD=pdflatex
P=Proposal
L=latex
RF=rm -rf

all:
	$(PD) $(P)
	bibtex $(P)
	$(PD) $(P)
	$(PD) $(P)

non-png:
	$(L) $(P)
	bibtex $(P)
	$(L) $(P)
	$(L) $(P)
	$(PD) $(P)

clean:
	$(RM) Proposal.bbl
	$(RM) Proposal.log
	$(RM) Proposal.blg
	$(RM) Proposal.aux
	$(RM) Proposal.pdf
	$(RM) Proposal.dvi	
