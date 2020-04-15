%The function regerr is a function developed to characterize a loadcell
% x is the vector of reference data in grams
% y is the matrix of measurement of the load cell (either in LSB or grams
% z is a optional string that defines the measurement unit of the data (it appears in the plots)
% if z is not specified, the plots are not shown
% ym is the vector cointaining the mean values of the measurement
% yr is the vector containing the regressed curve
% err is the non linearity error specified as ym-yr
% s is the standard deviation of the measurement
function [ym,yr,err,s]=regerr(x,y,z)
    ym=mean(y);
    s=std(y,0,1);
    [r,m,b]=regression(x,ym);
    yr=m*x+b;
    err=ym-yr;
    if nargin>2
        figure()
        errorbar(x,ym,s)
        hold on
        plot(x,yr,'--r');
        title('Measured values','FontSize',15)
        xlabel('Reference weight [g]','FontSize',15)
        ylabel(['[',z,']'],'FontSize',15)
        legend('Measured curve','Regression curve');
        figure()
        bar(s,'FaceAlpha',0.1)
        hold on
        bar(abs(err),'FaceAlpha',0.6)
        legend('Standard deviation','Non linearity residual');
        title(['Standard deviation and non linearity residual in [',z,']'],'FontSize',15);
        xlabel('Reference weight [g]','FontSize',15)
        ylabel(['[',z,']'],'FontSize',15)
    end
end