# Center & scale molecular dynamics coordinates for PCA
In the bitsxLaMarato hackathon, Ivonne Westermaier proposed as a challenge how to use principal component analysis (PCA) to analyze molecular dynamics trajectories of CLCN5 protein, the mutations of which are involved in Dent disease.

During her presentation, we spotted a potential way of improving the quality of the results provided by the PCA by doing a centering and scaling of the variables. In PCA analysis, when variables have very different variances (even if they are of the same units), a scaling should be done to prevent that the variables that have most variance mask the effect of those having less.
# What it does
Extracts the frames of the simulation in a text-readable format (PDB), then read the alpha carbon coordinates for each frame and builds a table, out of which a PCA analysis can be done and used to retrieve a different set of eigenvectors and eigenvalues.
# How we built it
Using both C++ programs to parse and extract the data, and a Python script to run the PCA and generate the eigenvectors and eigenvalues.
