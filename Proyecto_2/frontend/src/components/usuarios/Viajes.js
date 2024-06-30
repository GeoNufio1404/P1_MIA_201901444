import "../../index.css"
import { Contenedor_Principal } from '../shared/Funciones';

function Viajes() {
    return (
        <div className="Viajes">
            <div className="container Principal sombra w-50 p-1">
                <div className="col text-center mx-auto">
                    <br />
                    <h1 id="Titulo">Viajes</h1>
                    <br />
                </div>
            </div>
            <br />
            {Contenedor_Principal()}
        </div>
    )
}

export default Viajes;