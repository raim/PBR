
dat <- read.csv("scale_calibration.txt", sep=";",  header=TRUE, comment.char = "#")

calibrate <- dat[12:nrow(dat),]
dat <- dat[1:11,]

plot(dat,type="b")

dmL <- mean(diff(dat[,"mL"]))
dg <-  mean(diff(dat[,"g"]))
sd <- sd(diff(dat[,"g"]))

slope <- dmL/dg

cat(paste("CORRECTION FACTOR:", slope, "\n"))

plot(calibrate)
abline(a=0,b=1)
