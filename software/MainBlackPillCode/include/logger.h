#ifndef LOGGER_H
#define LOGGER_H

template <typename T>
class Logger
{

public:
    Logger(unsigned int dimensione) : dimensione_log(dimensione), indice_log(0), flag_finito_di_loggare(false)
    {

        log = new T[dimensione_log];
    }
    void logga(T val)
    {
        if (finito_di_loggare())
            return;

        log[indice_log] = val;
        indice_log++;
        if (indice_log >= dimensione_log)
        {
            flag_finito_di_loggare = true;
        }
    }

    bool finito_di_loggare()
    {
        return flag_finito_di_loggare;
    }
    void reset()
    {
        indice_log = 0;
        flag_finito_di_loggare = false;
    }
    unsigned int get_dimensione() { return dimensione_log; }
    T get_valore_loggato(unsigned int i) { return log[i]; }

private:
    T *log;
    unsigned int indice_log, dimensione_log;
    bool flag_finito_di_loggare;
};
#endif