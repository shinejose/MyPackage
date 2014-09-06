function print_table(t)
      io.write("{");
      for k,v in pairs(t) do
	    io.write(k);
	    io.write(" = ");
	    io.write(tostring(v));
	    io.write(" , ");
      end
      io.write("}\n");
end
