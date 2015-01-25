Function gcd(var a, b: Integer): Integer;
var t: Integer;
begin
    while b <> 0 do
        begin
            t := b;
            b := a mod b;
            a := t;
        end;
    gcd := a;
end;

var 
t, n, i, j, x: Integer;
a: array of Integer;

begin
    readln(t);
    for j := 1 to t do
        begin
            read(n);
            Setlength(a, n);
            
            for i := 0 to n - 1 do
                read(a[i]);
                
            x := a[0];
            for i := 1 to n - 1 do
                x := x * (a[i] div gcd(a[i], x));
            
            writeln(x);
        end
end.