import "../index.css";

function Footer() {
    return (

        <div className="Footer">
            <div className="b-footer sombra Principal">
                <div className="container">
                    <div className="row">
                        <div className="col-6">
                            <h5>Proyecto:</h5>
                            <p>OLC2, OLCScript</p>
                        </div>
                        <div className="col-6">
                            <h5>Datos Estudiante:</h5>
                            <p>Nombre: Geovanni Eduardo Nufio Illescas</p>
                            <p>Carnet: 201901444</p>
                        </div>
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
