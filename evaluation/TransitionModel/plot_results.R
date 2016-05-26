rm(list=ls())
#setwd("/home/coderus/Temp/share/Andrew/")
library(ggplot2)
library(reshape2)

plotResults <- function(dataset,similarityMetrics,similarityThres) {
  setwd(dataset)
  
  if(similarityMetrics == "lv") {
    filenames <- list.files()[grep(paste("^lv(?=.*\\.csv)",sep=''), list.files(), perl=TRUE)]
  }
  
  if(similarityMetrics == "dl") {
    filenames <- list.files()[grep(paste("^dl(?=.*\\.csv)",sep=''), list.files(), perl=TRUE)]
  }
  
  prefix=c()
  suffix=c()
  for (i in 1:length(filenames)) {
    prefix = c(prefix,unlist(strsplit(filenames[i], split='_', fixed = F))[3])
    suffix = c(suffix,unlist(strsplit(filenames[i], split='_', fixed = F))[4])
  }
  prefix=as.numeric(unique(prefix))
  suffix=as.numeric(unique(suffix))
  
  filename = sprintf("%s.csv",dataset)
  
  for (i in 1:length(prefix)) {
    res = data.frame(suffix_length = suffix,
                     lv = rep(0,length(suffix)),
                     dl = rep(0,length(suffix)),
                     jc = rep(0,length(suffix)),
                     lv_rnd = rep(0,length(suffix)),
                     dl_rnd = rep(0,length(suffix)),
                     jc_rnd = rep(0,length(suffix)))
    
    for (j in 1:length(suffix)) {
      fname = sprintf("%s_%s_%s_%s_%s",similarityMetrics,similarityThres,prefix[i],suffix[j],filename)
      fname_rnd = sprintf("rnd_%s_%s_%s",prefix[i],suffix[j],filename)
      dat = read.table(fname,header = FALSE,sep=",",col.names = paste0("V",seq_len(40)),fill = TRUE)
      #dat_rnd =read.table(fname_rnd,header = FALSE,sep=",",col.names = paste0("V",seq_len(40)),fill = TRUE)
      res$lv[j]=mean(dat$V1)
      res$dl[j]=mean(dat$V2)
      res$jc[j]=mean(dat$V3)
      # res$lv_rnd[j]=mean(dat_rnd$V1)
      # res$dl_rnd[j]=mean(dat_rnd$V2)
      # res$jc_rnd[j]=mean(dat_rnd$V3)
    }
    
    Res = reshape2::melt(res,id.vars = "suffix_length")
    require(grid)
    pdf(file=sprintf("plots/results_%s_%s_%s_%s.pdf",similarityMetrics,similarityThres,prefix[i],dataset),width=5,height=5)
    p=ggplot(Res,aes(x=suffix_length, y= value,color=variable)) + geom_point() + geom_line() + 
      scale_color_manual(values=c("green","red","blue","yellow","pink","lightblue"))+
      scale_y_continuous(breaks = seq(0,1,0.1), limits = c(0,1),labels =as.character(seq(0,1,0.1)))+
      scale_x_continuous(breaks = seq(min(suffix),max(suffix),1))+
      xlab("Predicted suffix length") + ylab("Average similarity")+
      theme(panel.background = element_rect(fill = 'white', colour = 'black',size=0.5)) + 
      theme(panel.grid.major = element_line(colour = 'lightgrey', size = 0.3))+
      theme(legend.key.width = unit(2.5, "line"))+
      theme(legend.background = element_rect(colour = 'white',size = 0.1, linetype='solid'))+
      labs(title = sprintf("results_%s_%s_%s_%s.pdf",similarityMetrics,similarityThres,prefix[i],dataset))
    print(p)
    dev.off()
  }
  
  setwd("../")
  
}

for (similarityMetrics in c("lv","dl")) {
  for (similarityThres in c(0.7,0.9)) {
    plotResults(dataset = "env_permit",similarityMetrics = similarityMetrics,similarityThres = similarityThres)
    plotResults(dataset = "act25",similarityMetrics = similarityMetrics,similarityThres = similarityThres)
    plotResults(dataset = "BPIC2011",similarityMetrics = similarityMetrics,similarityThres = similarityThres)
    plotResults(dataset = "BPIC2012",similarityMetrics = similarityMetrics,similarityThres = similarityThres)
    plotResults(dataset = "hospital",similarityMetrics = similarityMetrics,similarityThres = similarityThres)
  }
}

for (similarityMetrics in c("lv","dl")) {
  for (similarityThres in c(0.65,0.9)) {
    plotResults(dataset = "receipt_phase_env_permit",similarityMetrics = similarityMetrics,similarityThres = similarityThres)
    plotResults(dataset = "traf",similarityMetrics = similarityMetrics,similarityThres = similarityThres)
    plotResults(dataset = "venice",similarityMetrics = similarityMetrics,similarityThres = similarityThres)
  }
}
