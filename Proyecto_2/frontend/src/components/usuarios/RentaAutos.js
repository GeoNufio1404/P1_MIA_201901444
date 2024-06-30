import "../../index.css";
import { Contenedor_Principal } from '../shared/Funciones';

function RentaAutos() {
    return (
        <div className="RentaAutos">
            <div className="container Principal sombra w-50 p-1">
                <div className="col text-center mx-auto">
                    <br />
                    <h1 id="Titulo">Renta de Autos</h1>
                    <br />
                </div>
            </div>
            <br />
            {Contenedor_Principal()}
        </div>
    )
};

export default RentaAutos;