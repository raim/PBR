dat <- read.csv("Streulichtmessung.csv",skip=2)

od <- "Ideal.OD.WPA" # "WPA.Verd."
sc <- "Ava.Mittelw"

pdf("scatter_test1.pdf",width=5,height=4)
plot(dat[,od],dat[,sc],xlab="OD",ylab="Scatter, Intensity at 640 nm")
fit <- lm(dat[,sc]~dat[,od])
lines(dat[,od],predict(fit))
legend("right",legend=bquote(bold(R^2 == .(summary(fit)$r.squared))))
dev.off()
