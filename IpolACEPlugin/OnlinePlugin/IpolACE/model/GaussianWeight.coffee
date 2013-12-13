#
class GaussianWeight extends Model
    constructor: () ->
        super()

        @add_attr
            _name: "gaussian"
            _sigma: 1.0
            
        @add_attr
            sigma: @_sigma
    
    toString: () ->
        @_name.get()
        