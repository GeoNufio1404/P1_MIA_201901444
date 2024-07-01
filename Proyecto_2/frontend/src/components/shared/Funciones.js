
// Contenedor_Principal: Función que recibe un componente y lo envuelve en un contenedor principal.
const Contenedor_Principal = (Contenido, sombra) => {
    if (sombra) {
        return (
            <div className="container-fixed mx-auto sombra text-center Principal example-row p-2">
                <br /><hr className="Secundario" /><br />
                {Contenido}
                <br /><hr className="Secundario" /><br />
            </div>
        );
    } 
    return (
        <div className="container-fixed mx-auto text-center Principal example-row p-2">
            <br /><hr className="Secundario" /><br />
            {Contenido}
            <br /><hr className="Secundario" /><br />
        </div>
    );
};

// Margen_Contenedor_Secundario: Función que recibe un componente y lo envuelve en un contenedor secundario con margen.
const Contenedor_Secundario = (CodigoHtml, sombra) => {
    if (sombra) {
        return (
            <div className="Fondo p-4 sombra">
                <br /><hr className="Principal" /><br />
                {CodigoHtml}
                <br /><hr className="Principal" /><br />
            </div>
        );
    }
    return (
        <div className="Fondo p-4">
            <br /><hr className="Principal" /><br />
            {CodigoHtml}
            <br /><hr className="Principal" /><br />
        </div>
    );
};

const Separacion = () => {
    return (
        <div>
            <br /><hr className="Principal" /><br />
        </div>
    );
};

export { Contenedor_Principal, Contenedor_Secundario, Separacion };