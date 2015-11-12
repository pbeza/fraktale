function [] = koch(n)
  if (n == 0)
    x = [0; 1];
    y = [0; 0];
    line(x, y, 'Color', 'b');
    axis equal
    set(gca, 'Visible', 'off')
  else
    levelcontrol = 10^n;
    L = levelcontrol / (3^n);  
    l = ceil(L);
    kline(0, 0, levelcontrol, 0, l);
    axis equal
    set(gca, 'Visible', 'off')
    set(gcf, 'Name', 'Koch Curve')
  end
endfunction

function kline(x1, y1, x5, y5, limit)   
  length = sqrt((x5 - x1)^2 + (y5 - y1)^2); 
  if (length > limit)
    x2 = (2 * x1 + x5) / 3;
    y2 = (2 * y1 + y5) / 3;
    x3 = (x1 + x5) / 2 - (y5 - y1) / (2.0 * sqrt(3.0));
    y3 = (y1 + y5) / 2 + (x5 - x1) / (2.0 * sqrt(3.0));
    x4 = (2 * x5 + x1) / 3;
    y4 = (2 * y5 + y1) / 3;

    kline(x1, y1, x2, y2, limit);
    kline(x2, y2, x3, y3, limit);
    kline(x3, y3, x4, y4, limit);
    kline(x4, y4, x5, y5, limit);
  else 
    plotline(x1, y1, x5, y5);
  end
endfunction

function plotline(a1, b1, a2, b2)
  x = [a1; a2];
  y = [b1; b2];
  line(x, y);
endfunction