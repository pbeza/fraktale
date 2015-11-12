function sierpinski_carpet(i)
  %tic
  M = 0;
  for k=1:i
    M = [M,        M,      M;
         M, ones(3^(k-1)), M;
         M,        M,      M];
  end
  imagesc(M);
  colormap(gray);
  axis equal;
  axis off;
  %toc
endfunction