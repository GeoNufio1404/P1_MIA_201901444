import "../../index.css";

function Footer() {
    return (

        <div className="Footer sombra">
            <div className="Principal sombra">
                <div className="container">
                    <div className="row">
                        <div className="col-6">
                            <br />
                            <h4>Proyecto:</h4>
                            <hr className="Principal" /><br />
                            <p>AviCar, Manejo e Implementacion de Archivos</p>
                        </div>
                        <div className="col-6">
                            <br />
                            <h4>Datos Estudiante:</h4>
                            <hr className="Principal" /><br />
                            <p>Nombre: Geovanni Eduardo Nufio Illescas</p>
                            <p>Carnet: 201901444</p>
                        </div>
                        <br />
                    </div>
                </div>
            </div>
            <footer className="sombra Fondo">
                <p>© 2024 Geovanni Nufio, All rights reserved.</p>
            </footer>
        </div>
    );
}

export default Footer;
