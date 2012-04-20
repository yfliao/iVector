close all
addpath(genpath('../../Focal'))


[trainscores, trainlabels] = readScores('../../train.txt');
[devscores, devlabels] = readScores('../../dev.txt');
[testscores, testlabels] = readScores('../../nist.txt');

%trainscores = {log(trainscores{1}), log(trainscores{2})};
%devscores = {log(devscores{1}), log(devscores{2})};
%testscores = {log(testscores{1}), log(testscores{2})};

%Closed set
temp = [testlabels ~= 0];
Ctestscores = {testscores{1}(:, temp), testscores{2}(:, temp)};
Ctestlabels = testlabels(temp);




[alpha, beta] = train_nary_llr_fusion(devscores, devlabels);
loglh1 = apply_nary_lin_fusion(Ctestscores, alpha, beta);

[alpha, beta] = train_nary_llr_fusion(trainscores, trainlabels);
loglh2 = apply_nary_lin_fusion(Ctestscores, alpha, beta);


calref_plot({Ctestscores{1}, Ctestscores{2}, loglh1, loglh2}, Ctestlabels, {'Prim dialect', 'sec dialect', 'devtrained', 'traintrained'});