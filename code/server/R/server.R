
#' parse data from arduino modules, space-delimited data tables
#' where the first column is time in milliseconds and other columns
#' are measured data; on each power off-on cycle the arduino modules
#' currently append a new header on time starts at 0
#' NOTE and TODO: currently it searches and returns only the LAST
#' data set; it should return a ordered list of all datasets
#' TODO: filter data; collect averages, interpolate to time-points
#' skip redundant data and replace by resolution
#' @param file name of the data file to parse
parseModuleData <- function(file) {
    dat <- read.table(file,header=FALSE,sep=" ",stringsAsFactors=FALSE)

    ## only get last data
    headers <- grep("Time", dat[,1])
    skip <- max(headers)-1
    dat <- read.table(file,header=TRUE,skip=skip,sep=" ")
    dat
}

#' convert time in seconds/milliseconds to date object
#' NOTE and TODO: allow to pass several time stamps and check
#' linearity of arduino time
#' @param time time in seconds
#' @param timeStamp a named vector of a time in seconds, where
#' names are the corresponding date
#' @param format POSIX format of the time stamp, see \link{\code{strptime}}
stampTime <- function(time, timeStamp, format="%Y%m%d %X") {

    ## parse time stamps
    times <- strptime(names(timeStamp), format=format)
    ## get time0
    time0 <- times[1] - timeStamp[1]
    ## add time vector and return
    time0+time    
}


#' takes a time object and prepares a plotting canvas
#' with nice time axes
dateplot <- function(date, ylim) {

    start <- head(date,1)
    end <- tail(date,1)
    midnight <- trunc(seq(start, end, by="hours"),"days")
    noon <- midnight + 12*3600

    if ( missing(ylim) ) ylim <- c(0,1)
    plot(date,rep(1,length(date)),ylim=ylim, ylab=NA,axes=FALSE, col=NA,xlab=NA)
    ##axis(2); 
    mtext("time",1,2)
    axis.POSIXct(1,date,format="%H:%M")
    axis.POSIXct(3, at=midnight,labels=FALSE)
    axis.POSIXct(3, at=noon, format="%b %d",tcl=0)
    abline(v=as.numeric(midnight),lty=3)
    #box()
    legend("topleft",paste(c("start:","end: "),
                           format(c(start,end), "%b %d %H:%M:%S")),bg="#FFFFFF")
}
