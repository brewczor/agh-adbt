--XML publication
select 
	xmlelement(name flowers,
		xmlagg(
			xmlelement(name bouqet, 
				xmlattributes(trim(idkompozycji) as id, stan as quant, floor(cena) as price),
				xmlelement(name name, nazwa),
				xmlelement(name description, opis)
			)
		)
	) 
from kompozycje where stan > 4;
