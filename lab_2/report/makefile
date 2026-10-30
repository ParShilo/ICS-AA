MAIN = report
ENGINE = latexmk 

default: $(MAIN).pdf

$(MAIN).pdf: $(MAIN).tex preambula.tex parts/*.tex
	$(ENGINE) -xelatex -silent -shell-escape $(MAIN).tex

clean:
	$(ENGINE) -C
	rm -f *.synctex.gz

.PHONY: default clean $(MAIN).pdf