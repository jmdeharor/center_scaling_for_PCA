import argparse
import pickle

import numpy as np
import matplotlib.pyplot as plt

def main(input_file, output_dir):
    print('Using output directory ' + output_dir)
    print('Reading file from ' + input_file)
    all_coords = np.loadtxt(input_file)
    means = np.mean(all_coords, axis=0)
    stds = np.std(all_coords, axis=0)
    print('Saving std.dev.')
    np.savetxt(output_dir + '/stdevs.txt', stds)
    all_coords = all_coords - means
    all_coords = all_coords / stds
    covariance = np.cov(all_coords,rowvar=False)
    print('Saving means')
    np.savetxt(output_dir + '/means.txt', means)
    print('Saving covariance')
    np.savetxt(output_dir + '/covariance_matrix.txt', covariance)
    eigenvalues, eigenvectors = np.linalg.eigh(covariance)
    print('Saving eigenvalues')
    np.savetxt(output_dir + '/eigenvalues.txt', eigenvalues)
    print('Saving eigenvectors')
    np.savetxt(output_dir + '/eigenvectors.txt', eigenvectors)


if __name__ == '__main__':
    argparser = argparse.ArgumentParser()
    argparser.add_argument('file')
    argparser.add_argument('outputdir')
    args = argparser.parse_args()
    main(args.file, args.outputdir)
