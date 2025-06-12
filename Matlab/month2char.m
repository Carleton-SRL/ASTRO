function month = month2char(month0)
%{
© 2025 Yazan Chihabi
%}

    if month0 == 01
        month = 'Jan';
    elseif month0 == 02
        month = 'Feb';
    elseif month0 == 03
        month = 'Mar';
    elseif month0 == 04
        month = 'Apr';
    elseif month0 == 05
        month = 'May';
    elseif month0 == 06
        month = 'Jun';
    elseif month0 == 07
        month = 'Jul';
    elseif month0 == 08
        month = 'Aug';
    elseif month0 == 09
        month = 'Sep';
    elseif month0 == 10
        month = 'Oct';
    elseif month0 == 11
        month = 'Nov';
    elseif month0 == 12
        month = 'Dec';
    end
end