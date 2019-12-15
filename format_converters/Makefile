
.PHONY: all clean

all: pdb_merger eigen_data_to_cpptraj

pdb_merger: pdb_merger.cpp
	g++ -O3 $< -fopenmp -lstdc++fs -o $@

eigen_data_to_cpptraj: eigen_data_to_cpptraj.cpp
	g++ -O3 $< -o $@

clean:
	rm -f pdb_merger eigen_data_to_cpptraj
