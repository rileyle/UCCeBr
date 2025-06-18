#!/usr/bin/python3

import ROOT as root
import numpy as np
from matplotlib import pyplot as plt
import sys
import os

# The detector resolution is simulated as sigmaPars[det]*sqrt(E)
sigmaPars = {0:0.5}

# Histogram specifications
eMax       = 4096
nBins      = 4096

def readInputFile(fileName = "co60_sim_sort.inp"):

    try:
        inFile = open(fileName, 'r')
    except IOError:
        return
    
    line     = inFile.readline()
    words    = line.split()
    nDet     = int(words[0])

    line     = inFile.readline()
    words    = line.split()
    for det in range(nDet):
        sigmaPars[det] = float(words[det])

    line     = inFile.readline()
    words    = line.split()
    eMax     = float(words[0])

    line     = inFile.readline()
    words    = line.split()
    nBins    = int(words[0])

    inFile.close()

    return nDet, sigmaPars, eMax, nBins 

def Sort(fileName, nDet=1):

    try:
        inFile = open(fileName, 'r')
    except IOError:
        print('Error: unable to open file {0}'.format(fileName))
        return
    
    # Sort the output file.
    photopeakCounts = 0
    lastEvent  = -1
    lastDet    = -1
    lastEnergy = 0
    for line in inFile.readlines():
        words = line.split()
        event = int(words[0])
        det   = int(words[1])-1
        eSim  = float(words[2])

        if int(words[6]) == 1:
            photopeakCounts += 1
        
        # Fold in simulated resolution.
        
        sigma = sigmaPars[det]*np.sqrt(eSim)
        eRes = eSim + np.random.normal(scale=sigma)

        histosRaw[det].Fill(eSim)
        histos[det].Fill(eRes)

        # Symmetrized gamma-gamma matrix
        if event == lastEvent and det != lastDet:
            gam_gam.Fill(eRes, lastEnergy)
            gam_gam.Fill(lastEnergy, eRes)

            # 1332 keV cut
            if eRes > 1260 and eRes < 1400:
                cut_1332.Fill(lastEnergy)
            if lastEnergy > 1260 and lastEnergy < 1400:
                cut_1332.Fill(eRes)
        
        lastEvent = event
        lastDet = det
        lastEnergy = eRes
        
    print('{0:d} photopeak counts'.format(photopeakCounts))

    return 

nDet, sigmaPars, eMax, nBins = readInputFile()

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

gam_gam = root.TH2F("gamma_gamma", "Coincidence Matrix",
                    int(nBins/4), 0, eMax,
                    int(nBins/4), 0, eMax)
cut_1332 = root.TH1F("cut_1332", "1332 keV cut", nBins, 0, eMax)

Sort(sys.argv[1], nDet)

# Write histograms

outFileName, _ = os.path.splitext(sys.argv[1])
outFileName += ".root"
outFile = root.TFile(outFileName, "RECREATE")
for i in range(nDet):
    histosRaw[i].Write()
    histos[i].Write()
gam_gam.Write()
cut_1332.Write()

outFile.Close()
