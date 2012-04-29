function [cellscores, superscores, labels] = readScores(path)
  temp = dlmread(path);
  labels = mod(temp(:, 1), 13)';
  
  sys1cols = 2:13;%The columns with primary dialects
  sys2cols = [15:17 5:13];%The columns with secondary dialects

  cellscores = {temp(:, sys1cols)', temp(:, sys2cols)'};
  
  selection = (1:size(temp, 2) ~= 1) & (1:size(temp, 2) ~= 14);
  
  superscores = temp(:, selection)';


%temp = dlmread('train');

%trainscores = temp(:, 2:size(temp, 2))'; %First column is class labels
%trainlabels = double(temp(:, 1))';