# Nimo's template for Tex documents
# Original source from:
# https://tex.stackexchange.com/questions/40738/how-to-properly-make-a-latex-project
# @author: Wode "Nimo" Ni
# @date: 02/21/2018

# NOTE: Modify the constants to begin
#----------------------------------------------------------------------
# Constants

# directory where the pdf will get built
BUILDDIR := ./build
# the name of the main .tex file
BASENAME := animatepp-proposal
MAINOBJ  := $(BASENAME).pdf
MAINSRC  := $(BASENAME).tex
#----------------------------------------------------------------------

# You want latexmk to *always* run, because make does not have all the info.
# Also, include non-file targets in .PHONY so they are run regardless of any
# file of the given name existing.
.PHONY: $(MAINOBJ) all clean $(BUILDDIR)

# The first rule in a Makefile is the one executed by default ("make"). It
# should always be the "all" rule, so that "make" and "make all" are identical.
all: clean $(MAINOBJ)

# CUSTOM BUILD RULES

# In case you didn't know, '$@' is a variable holding the name of the target,
# and '$<' is a variable holding the (first) dependency of a rule.
# "raw2tex" and "dat2tex" are just placeholders for whatever custom steps
# you might have.

%.tex: %.raw
	./raw2tex $< > $@

%.tex: %.dat
	./dat2tex $< > $@

# MAIN LATEXMK RULE

# -pdf tells latexmk to generate PDF directly (instead of DVI).
# -pdflatex="" tells latexmk to call a specific backend with specific options.
# -use-make tells latexmk to call make for generating missing files.
# -jobname forces the build to happen in $(BUILDDIR)

# -interaction=nonstopmode keeps the pdflatex backend from stopping at a
# missing file reference and interactively asking you for an alternative.

$(MAINOBJ): $(MAINSRC) $(BUILDDIR)
	latexmk \
	-pdf \
	-pdflatex="pdflatex -interaction=nonstopmode" \
	-use-make \
	-jobname=$(BUILDDIR)/$(BASENAME) \
	$(MAINSRC)
	mv $(BUILDDIR)/$(BASENAME).pdf .

$(BUILDDIR):
	mkdir $(BUILDDIR)

# TODO: find a way to clean build directory
clean:
	# latexmk -CA
	rm -rf $(BUILDDIR)
