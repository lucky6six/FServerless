cc = g++
prom = controller
deps = function.h
obj = controller.o function.o
$(prom): $(obj)
	$(cc) -o $(prom) $(obj)
%.o: %.c $(deps)
	$(cc) -c $< -o $@
clean:
	rm -rf $(obj) $(prom)
