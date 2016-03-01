
## TODO: read all and handle data until next header line
## separately
dat <- read.delim("~/work/psi/PSIControl/offgas/arduino/data/20160112.txt",sep=" ",header=T,skip=5079)
time <- dat[,1]/1000/60/60 ## time in hours
co2 <- dat[,2] ## CO2 in ppm
o2 <- 100*dat[,3]/dat[,4] ## O2 in %
T <- dat[,5] ## T in °C

png("~/work/psi/PSIControl/offgas/arduino/data/20160112.png")
par(mfcol=c(4,1),mai=c(0,.75,0,0.05))
plot(time, co2, ylab="CO2 ppm",xlab="time [h]",type="l", log="y")
plot(time, co2, ylab="CO2 ppm",xlab="time [h]",type="l",ylim=c(0,1400))
plot(time, o2, ylab="O2 %",type="l")
plot(time, T, ylab="T °C",type="l")
dev.off()


## room recording, 20160113, 9:00-17:31
## start at ca. 9:00, stop at 17:31
dat <- read.delim("~/work/psi/PSIControl/offgas/arduino/data/20160113.txt",sep=" ",header=TRUE,skip=8)
time <- dat[,1]/1000/60/60 ## time in hours
time <- 17.5 - max(time) + time
co2 <- dat[,2] ## CO2 in ppm
o2 <- 100*dat[,3]/dat[,4] ## O2 in %
P <- dat[,4] ## total pressure in bar
T <- dat[,5] ## T in °C

png("~/work/psi/PSIControl/offgas/arduino/data/20160113.png",width=4,height=3,units="in",res=200)
par(mfcol=c(2,1),mai=c(0.1,.6,0.1,0.6),mgp=c(1.7,.6,0))
plot(time,co2,ylab="CO2 [ppm]",xlab="time [h]",type="l",ylim=c(0,1400),axes=FALSE)
axis(1,at=seq(1,24,1));axis(2);axis(3,at=seq(1,24,1),tcl=.5)
par(new=TRUE)
plot(time, o2, type="l", ylab=NA,xlab=NA,axes=F,col="red")
axis(4,col.axis="red",col.ticks="red",col="red")
mtext("O2 [%]", 4, 1.7, col="red")
plot(time, T, ylab="T [°C]",xlab="time [h]",type="l",axes=FALSE)
axis(1,at=seq(1,24,1),tcl=.5);axis(2)
par(new=TRUE)
plot(time, P, type="l", ylab=NA,xlab=NA,axes=F,col="red")
axis(4,col.axis="red",col.ticks="red",col="red")
mtext("P [ppm]", 4, 1.7, col="red")
dev.off()

## room recording, 20160119, 9:00-22:00
## start at ca. 9:00, stop at 21:00
dat <- read.delim("~/work/psi/PSIControl/offgas/arduino/data/20160119.txt",sep=" ",header=TRUE,skip=61127)
time <- dat[,1]/1000/60/60 ## time in hours
time <- time -min(time) + 9
co2 <- dat[,2] ## CO2 in ppm
o2 <- 100*dat[,3]/dat[,4] ## O2 in %
P <- dat[,4] ## total pressure in bar
T <- dat[,5] ## T in °C

png("~/work/psi/PSIControl/offgas/arduino/data/20160119.png",width=4,height=3,units="in",res=200)
par(mfcol=c(2,1),mai=c(0.1,.6,0.1,0.6),mgp=c(1.7,.6,0))
plot(time,co2,ylab="CO2 [ppm]",xlab="time [h]",type="l",ylim=c(0,1400),axes=FALSE)
axis(1,at=seq(1,24,1));axis(2);axis(3,at=seq(1,24,1),tcl=.5)
par(new=TRUE)
plot(time, o2, type="l", ylab=NA,xlab=NA,axes=F,col="red")
axis(4,col.axis="red",col.ticks="red",col="red")
mtext("O2 [%]", 4, 1.7, col="red")
plot(time, T, ylab="T [°C]",xlab="time [h]",type="l",axes=FALSE)
axis(1,at=seq(1,24,1),tcl=.5);axis(2)
par(new=TRUE)
plot(time, P, type="l", ylab=NA,xlab=NA,axes=F,col="red")
axis(4,col.axis="red",col.ticks="red",col="red")
mtext("P [ppm]", 4, 1.7, col="red")
dev.off()


##room recording, 20160301, 
## start at ca. 9:00, stop at 21:00
dat <- read.delim("~/work/hhu_2015/pbr_hackathon_201503/code/test/gas/data/20160301.txt",sep=" ",header=TRUE,skip=1)
time <- dat[,1]/1000/60/60 ## time in hours
time <- time -min(time) + 9
co2 <- dat[,2] ## CO2 in ppm
o2 <- 100*dat[,3]/dat[,4] ## O2 in %
P <- dat[,4] ## total pressure in bar
T <- dat[,5] ## T in °C

png("~/work/hhu_2015/pbr_hackathon_201503/code/test/gas/data/20160301.png",width=4,height=3,units="in",res=200)
par(mfcol=c(2,1),mai=c(0.1,.6,0.1,0.6),mgp=c(1.7,.6,0))
plot(time,co2,ylab="CO2 [ppm]",xlab="time [h]",type="l",ylim=c(0,1400),axes=FALSE)
axis(1,at=seq(1,24,1));axis(2);axis(3,at=seq(1,24,1),tcl=.5)
par(new=TRUE)
plot(time, o2, type="l", ylab=NA,xlab=NA,axes=F,col="red")
axis(4,col.axis="red",col.ticks="red",col="red")
mtext("O2 [%]", 4, 1.7, col="red")
plot(time, T, ylab="T [°C]",xlab="time [h]",type="l",axes=FALSE)
axis(1,at=seq(1,24,1),tcl=.5);axis(2)
par(new=TRUE)
plot(time, P, type="l", ylab=NA,xlab=NA,axes=F,col="red")
axis(4,col.axis="red",col.ticks="red",col="red")
mtext("P [ppm]", 4, 1.7, col="red")
dev.off()

