
// ==================================== Contenedores ====================================

// Función que recibe un componente y lo envuelve en un contenedor principal.
const Contenedor_Principal = (Titulo, Contenido) => {
    if (Titulo) {
        return (
            <div className="container-fixed mx-auto sombra text-center Principal example-row p-4">
                {Contenedor_Titulo(Titulo)}
                <Separacion />
                {Contenido}
                <Separacion />
            </div>
        );
    } else {
        return (
            <div className="container-fixed mx-auto sombra text-center Principal example-row p-4">
                <br />
                {Contenido}
                <Separacion />
            </div>
        );
    }
};

// Función que recibe un título y lo muestra en pantalla.
const Contenedor_Titulo = (Titulo) => {
    return (
        <div className="col text-center mx-auto sombra Enfasis">
            <br />
            <h1 id="Titulo">{Titulo}</h1>
            <br />
        </div>
    )
};

// Función que recibe un componente y lo envuelve en un contenedor secundario con margen.
const Contenedor_Secundario = (CodigoHtml, sombra) => {
    if (sombra) {
        return (
            <div className="Fondo p-4 sombra mx-auto">
                <br /><hr className="Principal" /><br />
                {CodigoHtml}
                <br /><hr className="Principal" /><br />
            </div>
        );
    }
    return (
        <div className="Fondo p-4 mx-auto">
            <br /><hr className="Principal" /><br />
            {CodigoHtml}
            <br /><hr className="Principal" /><br />
        </div>
    );
};

// ==================================== Divisiones ====================================

// Función que retorna un separador.
const Separacion = () => {
    return (
        <div>
            <br /><hr className="Principal" /><br />
        </div>
    );
};

// Función que recibe dos componentes y los divide en dos columnas de 6.
const Division6_6 = (ComponeneteIzq, ComponeneteDer) => {
    return (
        <div className="container-fluid">
            <div className="row">
                <div className="col-6">
                    {ComponeneteIzq}
                </div>
                <div className="col-6">
                    {ComponeneteDer}
                </div>
            </div>
        </div>
    );
};

// Función que recibe dos componentes y los divide en dos columnas de 4 y 8.
const Division4_8 = (ComponeneteIzq, ComponeneteDer) => {
    return (
        <div className="container-fluid">
            <div className="row">
                <div className="col-4">
                    {ComponeneteIzq}
                </div>
                <div className="col-8">
                    {ComponeneteDer}
                </div>
            </div>
        </div>
    );
};

export {
    Contenedor_Principal,
    Contenedor_Titulo,
    Contenedor_Secundario,
    Separacion,
    Division6_6,
    Division4_8
};