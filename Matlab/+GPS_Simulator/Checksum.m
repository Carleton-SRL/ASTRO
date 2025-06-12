function Checksum = Checksum(data)
%{
© 2025 Yazan Chihabi
%}
DataSum = uint64(sum(data));
    DataSumBin = bitget(DataSum,8:-1:1,"uint64");
    Checksum = 256-bin2dec(num2str(DataSumBin));
end