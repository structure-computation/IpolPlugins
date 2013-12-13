#
class RadialWeight extends Model
    constructor: () ->
        super()

        @add_attr
            _name: "radial (1/r)"
        
    toString: () ->
        @_name.get()
        