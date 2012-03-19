trainfile = 'Input/train.txt';
testfile = 'Input/test.txt';

addpath(genpath('C:\src\cpp\iVector\iVector\matlab\Focal\matlab\multifocal'))

%Read train file
fid = fopen(trainfile);
temp = fscanf(fid, '%f');
fclose(fid);

trainscores = cell(1);
trainscores{1} = temp(:, 2:size(temp, 2))';%First column is class labels
trainlabels = int16(temp(:,1))';

[alpha, beta] = train_nary_llr_fusion(trainscores, trainlabels);

%Read test file
fid = fopen(trainfile);
temp = fscanf(fid, '%');
fclose(fid);

testscores = cell(1);
testscores{1} = temp(:, 2:size(temp, 2))';
testlabels = int16(temp(:,1))';

loglh = apply_nary_lin_fusion(testscores, alpha, beta);


[llrs, decisions] = lre_detection(loglh);%Closed set
c = avg_detection_cost('cdet', decisions, testlabels);
disp(['c_det: ', num2str(c)])