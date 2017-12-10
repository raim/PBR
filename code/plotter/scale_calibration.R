
dat <- read.csv("scale_calibration.txt", sep=";", skip=1, header=TRUE)

dmL <- mean(diff(dat[,"mL"]))
dg <-  mean(diff(dat[,"g"]))
sd <- sd(diff(dat[,"g"]))

slope <- dmL/dg

cat(paste("CORRECTION FACTOR:", slope, "\n"))
