#ifndef MEDIAMOBILE_H
#define MEDIAMOBILE_H

template<typename T>
class Media_mobile
{
private:
    T somma ; 
    T* buffer;
    int dimensione_buffer;
    int indice;
    bool buffer_pieno;

public:
    Media_mobile(int dim ):dimensione_buffer(dim),  somma(T(0)), indice(0) ,buffer_pieno(false){
        
        buffer = new T[dimensione_buffer];
        reset();
    };
   
    T filtra( T valore) {
      
      somma -= buffer[indice];
      buffer[indice] = valore;
      somma += valore;
      indice = (indice + 1) % dimensione_buffer;
      if(indice == 0) buffer_pieno = true;  

      int denominatore = ( buffer_pieno ? dimensione_buffer : indice) ;
      if(denominatore > 0) {
        float media = somma / static_cast<T> (denominatore) ;
        //return ( (media > 0) ? (T) media+0.5f : media-0.5f) ;  //per gli impulsi (longint) va meglio così?
        return (T) media;
    } else {
        return valore;
      }
    }
    
    void reset()
    {
      indice = 0;
      somma = T(0);
      buffer_pieno = false;

      //inizializzo a zero tutti gli elementi, non è sufficiente il primo pensando 
      // al fatto dell'indice punatore la prima istruzione di filtra sottrae il valore di indice 

      for (int i = 0; i < dimensione_buffer; i++)  //TODO: Non sarebbe inutile?
         buffer[i] = T(0);
    }
};

#endif