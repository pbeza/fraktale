function sierpinski_triangle(A, B, C, n)
  if (n == 0)
    patch([A(1), B(1), C(1)], [A(2), B(2), C(2)], [0.0 0.0 0.0]);
  else
    sierpinski_triangle(A, (A + B) / 2, (A + C) / 2, n-1);
    sierpinski_triangle(B, (B + A) / 2, (B + C) / 2, n-1);
    sierpinski_triangle(C, (C + A) / 2, (C + B) / 2, n-1);
  endif
endfunction

% sierpinski_triangle([0 0], [1 0], [.5 .8], 8)