--XML publication
select 
	xmlelement(name flowers, 
		xmlelement(name bouqet, 
			xmlattributes(idkompozycji as id, stan as quant, floor(cena) as price),
			xmlelement(name name, nazwa),
			xmlelement(name description, opis)
		)
	) 
from kompozycje where stan > 4;
