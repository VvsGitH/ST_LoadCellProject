clearvars
close all
clc
%% Import data
a=dlmread('ReferenceWeights.csv',';'); %values from the reference scale
x=a(3,:);
y = dlmread('data.csv',','); %values from the loadcell
y=y';
y(201,:)=[];
yu=y(:,1:15); %data measured going upwards
yd=y(:,16:end-1); %data measured going downwards
%% Valori in LSB crescenti
[ymu,yru,erru,su]=regerr(x,yu,'LSB');
%% Valori in LSB decrescenti
yd=fliplr(yd);
[ymd,yrd,errd,sd]=regerr(x,yd,'LSB');
ku=ymu./x; %scale factors of stacking up measures
fsu=mean(ku); %mean scale factor stacking up
kd=ymd./x; %scale factors of stacking down measures
fsd=mean(kd); %mean scale factor stacking down
fs=mean([fsd,fsu]); %final scale factor
ysu=yu/fs; %measured data in grams stacking up
ysd=yd/fs; %measured data in grams stacking down
%% Valori in g crescenti
[ymsu,yrsu,errsu,ssu]=regerr(x,ysu,'g');
%% Valori in g decrescenti
[ymsd,yrsd,errsd,ssd]=regerr(x,ysd,'g');
