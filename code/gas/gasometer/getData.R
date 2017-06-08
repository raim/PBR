
file <- "offgas.txt" # "DATA.TXT"

## time map: mapping arduino time to real time
timeStamp <- NULL
timeStamp <- c(95,165347)
names(timeStamp) <- c("20170421 20:03:30","20170423 17:58:30")

## parse time stamps
times <- strptime(names(timeStamp), format="%Y%m%d %X")
## get time0
time0 <- times[1] - timeStamp[1]

## read in to get data ranges (separated by "Time" headers)
dat <- read.table(file,header=FALSE,sep=" ",stringsAsFactors=FALSE)

## only get last data
headers <- grep("Time", dat[,1])
skip <- max(headers)-1


dat <- read.table(file,header=TRUE,skip=skip,sep=" ")
time <- dat[,1]/1000 #sec #/3600/1000 # in hours
co2 <- dat[,2]
o2 <- dat[,3]/dat[,4]


png("offgas.png",width=5,height=3,res=300,units='in')
par(mai=c(.7,.7,0,.7),mgp=c(1,.3,0))
plot(time0+time,co2,type="l", ylab=NA,axes=TRUE, col="black",xlab=NA)
##axis(1);axis(2); 
mtext("time, h",1,2)
mtext("CO2, ppm",2,2)
par(new=TRUE)
plot(time,o2,type="l",ylab=NA,axes=FALSE, col="red",xlab=NA)
axis(4); mtext("O2, %",4,2)
dev.off()
