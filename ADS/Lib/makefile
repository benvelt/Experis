########## LIB MAKEFILE ##########

OBJECTS=$(wildcard *.o)

run: staticlib sharedlib

staticlib :
	ar cvr libGenDS.a $(OBJECTS)

sharedlib :
	gcc $^ -shared -o libGenDS.so $(OBJECTS) 

clean :
	-rm libGenDS.a
	-rm libGenDS.so

rundir : 
	$(MAKE) -C ../vector
	$(MAKE) -C ../doubleLL
	$(MAKE) -C ../stack
	$(MAKE) -C ../queue
	$(MAKE) -C ../heap
	$(MAKE) -C ../hashmap

commit : 
	$(MAKE) $@ -C ../vector
	$(MAKE) $@ -C ../doubleLL
	$(MAKE) $@ -C ../stack
	$(MAKE) $@ -C ../queue
	$(MAKE) $@ -C ../heap
	$(MAKE) $@ -C ../hashmap


.SILENT :
