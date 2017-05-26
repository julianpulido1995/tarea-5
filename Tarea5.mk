Resultados_hw5.pdf: Resultados_hw5.tex *.png
	pdflatex $<

*.png : *.txt plots_canal_ionico.py circuitoRC.py
	python plots_canal_ionico.py
	python circuitoRC.py

*.txt : a.out 
	./a.out

a.out : canal_ionico.c
	gcc -lm canal_ionico.c
