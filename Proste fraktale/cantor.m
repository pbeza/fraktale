function [x, y] = cantor(n)
  if n <= 0
    x = [0 1];
    y = [0 0];
  else
    [x0, y0] = cantor(n - 1);
    x = (1 / 3) * [x0 x0 + 2];
    y = [y0 y0];
  end
  plot(x, y, '.');
  hold off;
endfunction