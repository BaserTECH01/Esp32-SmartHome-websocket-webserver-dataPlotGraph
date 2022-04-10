

clear

if count(py.sys.path,'')==0
    insert(py.sys.path,int32(0),'');
end   

x=1;
repeat=1;
figure;

while repeat==1
 mod = py.importlib.import_module('weblisocket');
 py.importlib.reload(mod);
 data(x,:)=string(py.weblisocket.Connect());
 xlabel(x,:)=x;
 y=str2double(data(x,4));
 z=str2double(data(x,2));
 ylabel(x,:)=y;
 zlabel(x,:)=z;
 plot(xlabel,ylabel,"b");
 hold on
 plot(xlabel,zlabel,"r");
 drawnow;
 x=x+1;
end

