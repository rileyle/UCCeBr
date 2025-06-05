#!/usr/bin/python3

import ROOT as root
import numpy as np
from matplotlib import pyplot as plt
import sys
import os

# The detector resolution is simulated as the sum of two Gaussians
sigmaPar  = 0.75    # First energy resolution parameter

# Histogram specifications
eMax       = 4096
nBins      = 4096

def readInputFile(fileName = "CeBr3Sort.inp"):

    try:
        inFile = open(fileName, 'r')
    except IOError:
        return
    
    line     = inFile.readline()
    words    = line.split()
    nDet     = int(words[0])

    line     = inFile.readline()
    words    = line.split()
    sigmaPar = float(words[0])

    line     = inFile.readline()
    words    = line.split()
    eMax     = float(words[0])

    line     = inFile.readline()
    words    = line.split()
    nBins    = int(words[0])

    inFile.close()

    return nDet, sigmaPar, eMax, nBins 

def Sort(fileName, nDet=1):

    try:
        inFile = open(fileName, 'r')
    except IOError:
        print('Error: unable to open file {0}'.format(fileName))
        return
    
    # Sort the output file.
    photopeakCounts = 0
    for line in inFile.readlines():
        words = line.split()
        det   = int(words[1])-1
        eSim  = float(words[2])

        if int(words[6]) == 1:
            photopeakCounts += 1
        
        # Fold in simulated resolution.
        sigma = sigmaPar*np.sqrt(eSim)
        eRes = eSim + np.random.normal(scale=sigma)

        # TODO: Add threshold parameters


        histosRaw[det].Fill(eSim)
        histos[det].Fill(eRes)
        
    print('{0:d} photopeak counts'.format(photopeakCounts))

    return 

nDet, sigmaPar, eMax, nBins = readInputFile()

# Create histograms
histos = []
histosRaw = []
for i in range(nDet):
    hRaw = root.TH1F(f"enRaw{i}", f"Detector {i} energy",
                     nBins, 0, eMax)
    histosRaw.append(hRaw)
    h    = root.TH1F(f"en{i}", f"Detector {i} energy",
                     nBins, 0, eMax)
    histos.append(h)

Sort(sys.argv[1], nDet)

# Write histograms

outFileName, _ = os.path.splitext(sys.argv[1])
outFileName += ".root"
outFile = root.TFile(outFileName, "RECREATE")
for i in range(nDet):
    histosRaw[i].Write()
    histos[i].Write()

outFile.Close()
