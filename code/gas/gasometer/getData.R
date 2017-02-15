
dat <- read.table("DATA.TXT",header=FALSE,sep=" ")

## only get last data
headers <- grep("Time", dat[,1])
skip <- max(headers)-1


dat <- read.table("DATA.TXT",header=TRUE,sep=" ",skip=skip)
time <- dat[,1]/3600/1000 # in hours
co2 <- dat[,2]
o2 <- dat[,3]/dat[,4]


png("offgas_run100.png",width=5,height=3,res=300,units='in')
par(mai=c(.7,.7,0,.7),mgp=c(1,.3,0))
plot(time,co2,type="l", ylab=NA,axes=FALSE, col="black",xlab=NA)
axis(1);
axis(2); mtext("CO2, ppm",2,2)
par(new=TRUE)
plot(time,o2,type="l",ylab=NA,axes=FALSE, col="red",xlab=NA)
axis(4); mtext("O2, %",4,2)
dev.off()
