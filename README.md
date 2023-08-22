# AmBe_dose

AmBe dose simulations in open air and in a lead safe based on AmLi dose simulations by J. Busenitz, busenitz@retiree.ua.edu.

Prerequisite: Geant 4.10.04.p02 and ROOT 5.34/07 (later versions are ok)

Author: Mariia Fedkevych, mariia.fedkevych@gmail.com

-----------------------------------------------------------------------------------------------
General notes:
1) Basically, one calculates equivalent absorbed dose by scoring energy depositions in a tissue
phantom.
2) The tissue phantom is cylindrical, 30 cm in diameter and 100 cm in height.
The position and orientation of the phantom is described for each of the individual codes below.
3) The composition of the phantom is as defined by ICRP and implemented as a known material in
GEANT.
4) The simulation writes to standard output the energy (keV) and position (x,y,z in cm) of each
hit in the phantom and the particle producing the hit.  The simulation is set up so that
no other information is written to the simulation between the first hit in the first event and
the last hit in the last event.  To prepare the standard output file for analysis (using
analysis_txt.cc described below), strip out the simulation output preceding the first hit of
the first event and following the last hit of the last event.
5) If several simulation runs are done for a particular geometry and source, one may
concatenate the stripped files to produce a single file for analysis using "collect.job" script.
6) Note that all path names are as used to run the simulations on the Alabama group computing
cluster and must be revised to be run by another user at Alabama or run on another installation.
Check build_dose_<...>.job, dose_<...>.cc, GNUmakefile_dose_<...>, batch.job files.
------------------------------------------------------------------------------------------------

1. Download and unpack the dose_AmBe.tar.gz archive, e.g. run "tar -xf dose_AmBe.tar.gz" in Linux terminal
2. The folder contains 8 simulation subfolders starting with "ambe" which contain simulations for different cases, and corresponding .cc files starting with "dose", make files starting with "GNUmakefile_dose", .job files starting with "build" for the following cases:
    - if the name contains "gamma" gammas are simulated, otherwise neutrons
    - if the name contains "noW" it is done for the source without the outer tungsten capsule, otherwise for the source inside the outer tungsten capsule
    - if the name contains "surf" the simulation is done for the source inside a lead safe, otherwise it is for the source in open air:
        - Open air: Simulates AmBe primaries (gammas/neutrons) generated uniformly inside the inner capsule volume filled with AmO2/Be mixture.
                    The geometry is fixed with the the tissue phantom located just outside the capsule. (1 cm from center of the outermost capsule to edge of phantom). The cylindrical axes   
                    of the phantom and capsule are parallel and the midpoint of the source cavity lies in the plane bisecting the tissue phantom.  This roughly approximates a user holding 
                    the source close to body.
        - Lead safe: This simulates hits in the tissue phantom located outside the SURF source safe for the case of an AmBe source is placed inside the safe.  Only the neutrons emitted
                     by the source are simulated.  The outermost capsule is centered in the safe cavity. The cylindrical axes of the phantom and capsule are parallel and the midpoint of the 
                     source cavity lies in the plane bisecting the tissue phantom. The lead safe is assumed to a cube with external dimensions 30 cm on a side.  The world coordinates of the 
                     tissue phantom center in cm as well as its orientation in degrees measured relative to the z-axis. All rotations are in the x-z plane. The center of the safe is the 
                     world origin.
 
3. In the dose_AmBe folder, invoke build_<>.job, e.g. by running "./build_dose_ambe_gamma_tissue-icrp.job". This script defines environment variables, copies into place the appropriate codes in the src subdirectory, and builds the executable. 
4. Go to the corresponding "ambe" subfolder
5. Event input to the simulation is in HEPEvt format, provided by the code am241be.cc in case of gammas or am241be_neutron.cc in case of neutrons.   Build the generator executabl, e.g. g++ am241be.cc -o am241be.exe 
or similar on your system.  
6. Invoke the executable as:
./am241be.exe <number of events> > generator.data
in case of gammas or
./am241be_neutron
in case of neutrons (the number of events generated is set in the am241be_neutron.cc file).
7. Make batch.job executable, e.g. with "chmod u+x batch.job"
8. Run the simulation with "./batch.job > batch.o"
9. Run edit_log.job to strip the non-hit lines out of a log file by invoking sed. The first line deletes the lines in the log file preceding the hits and the second line deletes the
lines after the last hit.
./edit_log.job batch.o
(I had to run it twice to get the batch.o file trimmed correctly).
10. Delete out.file, e.g. "rm out.hist"
11. For root to be able to deal with large arrays (on Linux/Unix OS  systems, the memory required for these
arrays may exceed the stack limit and ROOT simply exits), the ulimit command can be used to set adequate limits:
    ulimit -S -a  ! displays soft limit on stack size
    ulimit -S -s xxxxx ! sets soft limit on stack size to xxxxx
    ulimit -H -a  ! displays hard limits on stack size
12. Start root and run 
    .L analysis_txt.cc
and then
    analysis_txt(textfile,histfile,xedge);

where
    -textfile is the name of the stripped simulation log file containing the hits 
    -histfile is the name of the output file in which filled histograms are saved
    -xedge is the minimum value of x for hits in the phantom.
    -Example: analysis_txt("batch.o","out.hist", -1.0);

The code divides the volume containing the phantom into rectangular cells of side 0.5 cm
and sums the energy deposits in each cell, weighted the quality factor. Along the way, various
histograms (see code for definitions) are also filled.
The cells are then ranked in order of decreasing equivalent absorbed energy and then
text output is produced as shown in the following example:

    Number of hits out of range: 57
    Number of hits in run: 15518832
    Total equivalent energy deposited in phantom: 4.12943e+08 keV
    Total equivalent energy deposited in hottest 1000 g: 1.28005e+08 keV
    Total equivalent energy deposited in hottest 100 g: 2.34287e+07 keV
    Total equivalent energy deposited in hottest 10 g: 3.43066e+06 keV
    Total equivalent energy deposited in hottest 1 g: 447013 keV
    rank, total equivalent energy (keV),(uncertainty (keV)),x,y,z: 0 64736.1 (130.138) -6.25 3.75 0.75
    rank, total equivalent energy (keV),(uncertainty (keV)),x,y,z: 1 58385 (115.405) -0.25 -5.25 -6.25
    rank, total equivalent energy (keV),(uncertainty (keV)),x,y,z: 2 58308 (275.921) -9.25 -11.75 12.75
    rank, total equivalent energy (keV),(uncertainty (keV)),x,y,z: 3 55563.3 (178.355) -11.75 4.25 9.75
    rank, total equivalent energy (keV),(uncertainty (keV)),x,y,z: 4 55252.9 (248.323) -13.75 0.25 6.25
    rank, total equivalent energy (keV),(uncertainty (keV)),x,y,z: 5 54157.9 (256.167) -14.75 -0.75 -1.75
    rank, total equivalent energy (keV),(uncertainty (keV)),x,y,z: 6 50752.7 (508.413) -14.25 0.75 3.25
    rank, total equivalent energy (keV),(uncertainty (keV)),x,y,z: 7 49857.5 (433.77) -13.25 5.25 4.75
    rank, total equivalent energy (keV),(uncertainty (keV)),x,y,z: 8 49807.8 (174.403) -6.75 8.75 4.75
    rank, total equivalent energy (keV),(uncertainty (keV)),x,y,z: 9 49042.4 (530.648) -13.75 -3.75 3.25

where
    - The number of hits out of range is the number of hits that don't fall within the nominal phantom volume (due probably to the GEANT4 variable used to define the step start point). Just 
      make sure this value is small compared to the total number of hits in the run
    - The total number of hits in the run is the total number of hits in the input file
    - The following 5 lines are the total equivalent energy deposited in all cells, the top 8000 cells, the top 800 cells, the top 80 cells, and the top 8 cells, respectively.
    - Finally, the last 10 lines give the equivalent energy and location of the 10 cells with the highest equivalent energy deposits.
I saved the output to out.log.
13. To estimate absorbed dose equivalent in mrem
    - start with equivalent energy deposited in highest cell
    - multiply by 1.602e-16 to convert keV to J
    - multiply by 8000 to get absorbed dose equivalent in J/kg (Sv), assuming tissue density of 1 g/cc
    - multiply by 100000 to convert from Sv to mrem
    - multiply by [(source emissions/hr)/number of emissions simulated] to get absorbed dose rate in mrem/hr.
